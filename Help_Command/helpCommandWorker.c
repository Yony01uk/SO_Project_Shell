#include "helpCommand.h"

int main(int argc, char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char *command = (char *)malloc(sizeof(char)*256);
    char *file_location = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    char *result = (char *)malloc(sizeof(char)*256);
    FILE *file;
    file_location = GetFileName(argv[0],DIR_INPUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        result = helpCommandWorker(argv[3]);
    }
    else
    {
        fclose(file);
        file = fopen(data,"r");
        data = fgets(data,10000,file);
        result = helpCommandWorker(data);
        fclose(file);
    }
    file_location = GetFileName(argv[0],DIR_OUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        file = fopen(OUTPUT,"w");
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