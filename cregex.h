
//
// cregex.h
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#ifndef _CREGEX_H_
#define _CREGEX_H_

#include <regex.h>

typedef struct {
 char       *pattern;
 char       *string;
 regex_t    *comp;
 regmatch_t *match;
}cregex_t;
  

#endif 
