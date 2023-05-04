#include "setCommand.h"

int main(int argc,char *argv[])
{
    char *file_location_in = (char *)malloc(sizeof(char)*256);
    char *file_location_out = (char *)malloc(sizeof(char)*256);
    char *file_out = (char *)malloc(sizeof(char)*256);
    char *result = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    file_location_in = GetFileName(argv[0],DIR_INPUT);
    file_location_out = GetFileName(argv[0],DIR_OUT);
    file_out = GetFileName(argv[0],OUTPUT);
    FILE *file;
    file = fopen(file_location_in,"r");
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
        data = ReadFile(file);
        char *args[2];
        args[0] = (char *)malloc(sizeof(char)*256);
        args[1] = (char *)malloc(sizeof(char)*256);
        Tokenize(args,data," ");
        argv[3] = args[0];
        argv[4] = args[1];
        result = setCommandWorker(argv);
        fclose(file);
    }
    file = fopen(file_location_out,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        file = fopen(file_out,"w");
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