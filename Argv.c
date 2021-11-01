//
// Created by blast on 2021/5/24.
//
#include <string.h>

int myargc;
char **myargv;


int check_Param(char *param) {
    int i;
    for(i = 1; i < myargc; ++i) {
        if(strcmp(myargv[i], param) == 0) {
            return i;
        }
    }
    return 0;
}