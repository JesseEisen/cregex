
//
// example.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cregex.h"


int main(void)
{
    char *string  = "2017/11/28";
    char *pattern = "([0-9]{4})/([0-9]{2})/([0-9]{2})";

    cregex_t  reg;
    
    //init crgex with max match result
    cregex_init(&reg, 10);

    if(cregex_match(&reg, pattern, string) <= 0) {
        printf("match error: %s\n", cregex_get_err(&reg));
        return -1;
    }

    cregex_dump_match(&reg);
    cregex_free(&reg);

    return 0;
}
