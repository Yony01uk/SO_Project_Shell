#include "outputsCommands.h"

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
        printf("%s\n",argv[i]);
    char *arg1 = (char *)malloc(sizeof(char)*256);
    char *operator = (char *)malloc(sizeof(char)*256);
    char *arg2 = (char *)malloc(sizeof(char)*256);
    arg1 = argv[1];
    operator = argv[2];
    arg2 = argv[3];
    if(strcmp(operator,"l_a") == 0)
        return LeftAngular(arg1,arg2);
    if(strcmp(operator,"d_l_a") == 0)
        return DoubleLeftAngular(arg1,arg2);
    if(strcmp(operator,"r_a") == 0)
        return RightAngular(arg1,arg2);
    return -1;
}