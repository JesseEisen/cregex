
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


void 
cregex_init(cregex_t * self) {
  self->comp = malloc(sizeof(regex_t) + more);
}


int
cregex_parse(cregex_t *self, char *pattern, char *string) {
  self->pattern = strdup(pattern);
  self->string  = strdup(string);
  
}



