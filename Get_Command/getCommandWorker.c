#include "getCommand.h"
#include<sys/dir.h>

int main(int argc,char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char *data = (char *)malloc(sizeof(char)*256);
    FILE *file;
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(argv[0],DIR_INPUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    char *result = (char *)malloc(sizeof(char)*256);
    if(strcmp(data,"NONE") == 0)
        result = getCommandWorker(argv[3]);
    else
    {
        fclose(file);
        file = fopen(data,"r");
        data = fgets(data,10000,file);
        result = getCommandWorker(data);
    }
    fclose(file);
    file_location = GetFileName(argv[0],DIR_OUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        file_location = GetFileName(argv[0],OUTPUT);
        file = fopen(file_location,"w");
        fputs(result,file);
    }
    else
    {
        fclose(file);
        file = fopen(data,"w");
        fputs(result,file);
        fclose(file);
    }
}