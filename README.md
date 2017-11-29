##  Introduction

This is a wrapper of c standard lib `regex.h`. And it is still in progress.


## Build And Test

```
$ make 
$ ./test
```

## Example

```c
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

```

Then we compile and run it.

```bash
$ valgrind --leak-check=full ./example
  
  ==15963== Memcheck, a memory error detector
   ==15963== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
   ==15963== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
   ==15963== Command: ./example
   ==15963== 

   match result 

   [0]: 2017/11/28 
   [1]: 2017 
   [2]: 11 
   [3]: 28 

   ==15963== 
   ==15963== HEAP SUMMARY:
   ==15963==     in use at exit: 0 bytes in 0 blocks
   ==15963==   total heap usage: 134 allocs, 134 frees, 30,202 bytes allocated
   ==15963== 
   ==15963== All heap blocks were freed -- no leaks are possible
   ==15963== 
   ==15963== For counts of detected and suppressed errors, rerun with: -v
   ==15963== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)=

```

## Functions

Here are some interfaces can use outside. But more maybe provided.

```c
void cregex_init(cregex_t *, int );
int  cregex_match(cregex_t *, char *, char *);
int  cregex_match_all(cregex_t *, char *, char *);
void cregex_dump_match(cregex_t *);
char *cregex_get_match(cregex_t *, int);
void cregex_free(cregex_t *);
```

And some macros used to set some items

```c
cregex_set_cflag(self, flag)  
cregex_set_eflag(self, flag)  
cregex_set_nmatch(self, num)  
cregex_get_err(self)          
```

More about `cflag` and `eflag` can refer `man regex`.

## License

(The MIT License)

Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>

