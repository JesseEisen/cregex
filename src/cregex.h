
//
// cregex.h
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#ifndef _CREGEX_H_
#define _CREGEX_H_

#include <regex.h>

#define ERR_BUF_SIZE  100

typedef struct {
 char       *pattern;
 char       *string;
 regex_t    *comp;
 regmatch_t *match_group;
 int        nmatch; 
 int        nmatched;
 int        cflag; 
 int        eflag;
 char       **matched;
 char       errbuf[ERR_BUF_SIZE];
} cregex_t;
 

#define cregex_set_cflag(self, flag)  (self)->cflag = (flag)
#define cregex_set_eflag(self, flag)  (self)->eflag = (flag)
//max match for regex group
#define cregex_set_nmatch(self, num)  (self)->nmatch = (num) 
#define cregex_get_err(self)          (self)->errbuf

void cregex_init(cregex_t *, int );
int  cregex_match(cregex_t *, char *, char *);
int  cregex_match_all(cregex_t *, char *, char *);
void cregex_dump_match(cregex_t *);
char *cregex_get_match(cregex_t *, int);
void cregex_free(cregex_t *);


#endif 
