#include "unsetCommand.h"

int main(int argc,char *argv[])
{
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
            return -1;
    }
    else
    {
        fclose(file);
        file = fopen(data,"r");
        fgets(data,10000,file);
        char *copy = (char *)malloc(sizeof(char)*256);
        for(int i =0; i < strlen(data); i++)
        {
            if(data[i] == ' ')
            {
                copy = strncpy(copy,data,i);
                break;
            }
        }
        char *result = (char *)malloc(sizeof(char)*256);
        result = unsetCommandWorker(copy);
        if(strcmp(result,"FAIL") == 0)
            return -1;
    }
    file_location = GetFileName(argv[0],DIR_OUT);
    file = fopen(file_location,"r");
    data = fgets(data,100000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        file_location = GetFileName(argv[0],OUTPUT);
        file = fopen(file_location,"w");
        fputs("NONE",file);
        fclose(file);
    }
    else
    {
        fclose(file);
        file = fopen(data,"w");
        fputs("NONE",file);
        fclose(file);
    }
}