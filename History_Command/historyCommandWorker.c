#include<unistd.h>
#include "historyWorker.h"

//deben existir al menos 2 elementos en *argv[]
int main(int argc,char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char *result = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    char *file_location = (char *)malloc(sizeof(char)*256);
    char *command = (char *)malloc(sizeof(char)*256);
    FILE *file;
    file_location = GetFileName(argv[0],DIR_INPUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        for(int i = 3; i < argc; i++)
        {
            if(i == 1)
                command = strcpy(command,argv[i]);
            else
            {
                command = strcat(command," ");
                command = strcat(command,argv[i]);
            }
        }
    }
    else
    {
        fclose(file);
        file = fopen(data,"r");
        data = fgets(data,10000,file);
        command = strcpy(command,data);
        fclose(file);
    }
    result = historyCommandWorker(command);
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