#include "unsetCommand.h"

int main(int argc,char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char *data = (char *)malloc(sizeof(char)*256);
    char *file_location = (char *)malloc(sizeof(char)*256);
    FILE *file;
    file_location = GetFileName(argv[0],DIR_INPUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        char *result = (char *)malloc(sizeof(char)*256);
        result = unsetCommandWorker(argv[3]);
        if(strcmp(result,"FAIL") == 0);
            exit(-1);
    }
    else
    {
        fclose(file);
        file = fopen(data,"r");
        data = fgets(data,10000,file);
        char *result = (char *)malloc(sizeof(char)*256);
        result = unsetCommandWorker(data);
        if(strcmp(result,"FAIL") == 0)
            exit(-1);
    }
}