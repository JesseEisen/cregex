
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
    char *string = "Hello, Today is 2017/11/27";
    char *pattern = "^" str "([0-9]{4})/([0-9]{2})/([0-9]{2})$";
    
    cregex_init(&reg, 10);
    if(cregex_match(&reg, pattern, string) == 0) {
        printf("\n match failed: %s\n", reg.errbuf);
    }
    
    cregex_dump_match(&reg);
    cregex_free(&reg);

    return 0;
}
