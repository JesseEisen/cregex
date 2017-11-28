
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
#define FALSE  0
#define TRUE   1

#define cregex_set_cflag(self, flag)  self->cflag = (flag)
#define cregex_set_eflag(self, flag)  self->eflag = (flag)
#define cregex_get_err(self)          self->errbuf
/*
 * strdup 
 */

char *
strdup(const char *str) {
    if(!str)  return NULL;

    int len = strlen(str) + 1;
    char *buf = malloc(len);
    if(buf) memcpy(buf, str, len);
    return buf;
}


void 
cregex_init(cregex_t *self, int nmatch) {
  self->comp     = malloc(sizeof(regex_t) + more);
  self->nmatch   = nmatch;
  self->nmatched = 0;
  self->eflag    = 0;
  self->cflag    = REG_EXTENDED | REG_ICASE;
}


int
cregex_parse(cregex_t *self) {
  int res, i, size, nmatched;
  regmatch_t *group;
  char **matched;
  
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

  self->matched = malloc(sizeof(char *) * self->nmatch);
  if(!self->matched) return -1;

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

  regfree(self->comp);
  return 0;
}

int 
cregex_match(cregex_t *self, char *pattern, char *string) {
  self->pattern = strdup(pattern);
  self->string  = strdup(string);

  if(cregex_parse(self) < 0) return FALSE;
    
  return TRUE;
}

void
cregex_dump_match(cregex_t *self) {
    int i; 
    
    printf("\n match result \n\n");
    for(i = 0; i < self->nmatched; i++) {
        printf("%4c [%d]: %s \n",' ', i, self->matched[i]);
    }
    printf("\n");
}

char *
cregex_get_match(cregex_t *self, int index) {
    if (index < 0 || index > self->nmatched - 1)  return NULL;

    return self->matched[index];
}

void 
cregex_free(cregex_t *self) {
    if(self->comp)    free(self->comp);
    if(self->pattern) free(self->pattern);
    if(self->string)  free(self->string);
    if(self->match_group) free(self->match_group);

    for(int i = 0; i < self->nmatched; i++) {
        if(self->matched[i]) free(self->matched[i]);
    }
    free(self->matched);
}
