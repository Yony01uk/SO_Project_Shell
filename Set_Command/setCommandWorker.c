#include "setCommand.h"

int main(int argc,char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char *file_location = (char *)malloc(sizeof(char)*256);
    char *result = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    FILE *file;
    file_location = GetFileName(argv[0],DIR_INPUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        result = setCommandWorker(argv);
    }
    else
    {
        fclose(file);
        file = fopen(data,"r");
        data = fgets(data,10000,file);
        char *args[2];
        args[0] = (char *)malloc(sizeof(char)*256);
        args[1] = (char *)malloc(sizeof(char)*256);
        Tokenize(args,data," ");
        argv[3] = args[0];
        argv[4] = args[1];
        result = setCommandWorker(argv);
        fclose(file);
    }
    file_location = GetFileName(argv[0],DIR_OUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        file_location = GetFileName(argv[0],OUTPUT);
        file = fopen(file_location,"w");
        fputs(result,file);
        fclose(file);
    }
    else
    {
        fclose(file);
        file = fopen(data,"w");
        fputs(result,file);
        fclose(file);
    }
}