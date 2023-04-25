#include<stdio.h>
#include "cdCommand.h"

int main(int argc,char *argv[])
{
    char *data = (char *)malloc(sizeof(char)*256);
    data = GetCurrentDirectory();
    printf("%s\n",data);
    cdCommand(argv[1]);
    data = GetCurrentDirectory();
    printf("%s\n",data);
    return 0;
}