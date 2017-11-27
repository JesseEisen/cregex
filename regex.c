
//
// regex.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define str  "[a-zA-z, ]*"

int
main(int argc, char **argv) {
   // char *string = "Hello, Today is 2017/11/27";
   // char *pattern = "^" str "([0-9]{4})/([0-9]{2})/([0-9]{2})$";
    char *string = "paranormal";
    char *pattern = "(a.)";
    regex_t *comp = malloc(sizeof(regex_t) + 16);
    regmatch_t match_group[10];
    int res, i, size = 0; 
    char * match, *temp; 

    res = regcomp(comp, pattern, REG_EXTENDED|REG_ICASE);
    if(res)  return 0;

    res = regexec(comp,string,10, match_group,0);
    if(res)  return 0;

    printf("\n string: %s\n", string);
    temp = string;
    for(i = 0; i < 10; i++) {
        if(match_group[i].rm_so < 0 || match_group[i].rm_eo < 0) {
            if(i == 1)  break; // means there not find
        
            temp +=  match_group[i-1].rm_eo;
            res = regexec(comp, temp, 10, match_group,0);
            if(res) break;
            i = 0;
            continue;
        }
        
        if(i > 0)
        {  
            size = match_group[i].rm_eo - match_group[i].rm_so;
            match  = malloc(size + 1);
            memcpy(match,temp+match_group[i].rm_so, size);
            match[size] = '\0';

            printf("%6s \n", match);
            free(match);
        }
    }

    printf("\n");
    regfree(comp);
    return 0;
    

}
