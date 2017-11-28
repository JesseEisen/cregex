
//
// test.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include "cregex.h"

#define str "[a-zA-z, ]*"

int 
main(void) {
    cregex_t  reg;
    
    printf("\n  match group test: \n");
    char *string = "Hello, Today is 2017/11/27";
    char *pattern = "^" str "([0-9]{4})/([0-9]{2})/([0-9]{2})$";
    
    cregex_init(&reg, 10);
    if(cregex_match(&reg, pattern, string) == -1) {
        printf("\n match failed: %s\n", reg.errbuf);
    }
    cregex_dump_match(&reg);
    cregex_free(&reg);

    printf("\n  match all group test: \n");
    char *string2  = "paranormal";
    char *pattern2 = "(a.)";
    if(cregex_match_all(&reg,pattern2,string2) == -1) {
        printf("\n match failed: %s\n", reg.errbuf);
    }
    cregex_dump_match(&reg);
    cregex_free(&reg);

    printf("\n  compiler regex error: \n");
    char *string3  = "hello";
    char *pattern3 = "he(ll?o";
    if(cregex_match(&reg,pattern3, string3) == -1) {
        printf("\n\tregex compiler failed: %s\n", reg.errbuf);
    }
    cregex_free(&reg);

    return 0;
}
