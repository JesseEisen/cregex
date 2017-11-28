
//
// cregex.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cregex.h"


#define more 16

/*
 * Strdup 
 */

char *
Strdup(const char *str) {
    if(!str)  return NULL;

    int len = strlen(str) + 1;
    char *buf = malloc(len);
    if(buf) memcpy(buf, str, len);
    return buf;
}

/*
 * init cregex structure
 */

void 
cregex_init(cregex_t *self, int nmatch) {
  self->nmatch   = nmatch;
  self->nmatched = 0;
  self->eflag    = 0;
  self->cflag    = REG_EXTENDED | REG_ICASE;
}


/*
 * regex result parse
 */

static int 
cregex_parse(cregex_t *self) {
  int        i;
  int        size;
  int        nmatched;
  char       **matched;
  regmatch_t *group;
  
  self->nmatched = 0;
  
  self->matched = malloc(sizeof(char *) * self->nmatch);
  if(!self->matched) return 0;

  group   = self->match_group;
  matched = self->matched; 
  nmatched = self->nmatched;
  for(i = 0; i < self->nmatch; i++) {
      if(group[i].rm_so < 0 || group[i].rm_eo < 0) {
        break;
      }

      size = group[i].rm_eo - group[i].rm_so;
      matched[nmatched] = malloc(size + 1);
      memcpy(matched[nmatched], self->string + group[i].rm_so, size);
      matched[nmatched++][size] = '\0';
  }

  self->nmatched = nmatched;

  return 1;
}


/*
 * parse all pattern in the string
 */

static int 
cregex_parse_all(cregex_t *self) {
  int        i;
  int        size;
  int        nmatched;
  int        res;
  char       *temp;
  char       **matched;
  regmatch_t *group;
  
  self->nmatched = 0;
  
  self->matched = malloc(sizeof(char *) * self->nmatch);
  if(!self->matched) return 0;

  temp     = self->string;
  group    = self->match_group;
  matched  = self->matched; 
  nmatched = self->nmatched;
  for(i = 0; i < self->nmatch; i++) {
      if(group[i].rm_so < 0 || group[i].rm_eo < 0) {
        if(i == 1) break;

        temp += group[i-1].rm_eo;
        res = regexec(self->comp, temp, self->nmatch, group, self->eflag);
        if(res) {
            regerror(res, self->comp, self->errbuf, ERR_BUF_SIZE);
            break;
        }
        i = 0;
        continue;
      }
    
      if(i > 0) {
        size = group[i].rm_eo - group[i].rm_so;
        matched[nmatched] = malloc(size + 1);
        memcpy(matched[nmatched], temp + group[i].rm_so, size);
        matched[nmatched++][size] = '\0';
      }
  }

  self->nmatched = nmatched;
    
  return 1;
}


/*
 * regex compile and exec
 */

static int
cregex_exec(cregex_t *self) {
  int res;
  
  self->comp = malloc(sizeof(regex_t) + more);
  if(!self->comp)  return 0;

  res = regcomp(self->comp, self->pattern, self->cflag);
  if(res) {
    regerror(res, self->comp, self->errbuf, ERR_BUF_SIZE);
    return -1;
  }

  self->match_group = malloc(sizeof(regmatch_t) * self->nmatch);
  if(!self->match_group)  return -1;

  res = regexec(self->comp, 
                self->string, 
                self->nmatch, 
                self->match_group, 
                self->eflag);
  if(res) {
    regerror(res, self->comp, self->errbuf, ERR_BUF_SIZE);
    return -1;
  }

  return 1;
}


/*
 * match 
 */

int 
cregex_match(cregex_t *self, char *pattern, char *string) {
  int res;

  self->pattern = Strdup(pattern);
  self->string  = Strdup(string);

  if((res = cregex_exec(self))  <= 0) return res;
  if((res = cregex_parse(self)) <= 0) return res;
  
  return res;
}


/*
 * match all
 */
int 
cregex_match_all(cregex_t *self, char *pattern, char *string) {
    int res;

    self->pattern = Strdup(pattern);
    self->string  = Strdup(string);

    if((res = cregex_exec(self)) <= 0)     return res;
    if((res = cregex_parse_all(self)) < 0) return res;

    return res;
}


/*
 * dump current self matched
 */

void
cregex_dump_match(cregex_t *self) {
    int i; 
    
    printf("\n%4c match result \n\n", ' ');
    for(i = 0; i < self->nmatched; i++) {
        printf("%4c [%d]: %s \n",' ', i, self->matched[i]);
    }
    printf("\n");
}


/*
 *  get match by index
 */

char *
cregex_get_match(cregex_t *self, int index) {
    if (index < 0 || index > self->nmatched - 1)  return NULL;

    return self->matched[index];
}


/*
 * free 
 */

void 
cregex_free(cregex_t *self) {
    //free regex 
    regfree(self->comp);
    
    if(self->comp)    free(self->comp);
    if(self->pattern) free(self->pattern);
    if(self->string)  free(self->string);
    if(self->match_group) { 
        free(self->match_group); 
        self->match_group = NULL; 
    }

    if(self->matched) {
        for(int i = 0; i < self->nmatched; i++) {
            if(self->matched[i]) free(self->matched[i]);
        }
        free(self->matched);
        self->matched = NULL;
    }
    
}
