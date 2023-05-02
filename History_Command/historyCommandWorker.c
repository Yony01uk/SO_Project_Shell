#include<unistd.h>
#include "historyWorker.h"

//deben existir al menos 2 elementos en *argv[]
int main(int argc,char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char *result = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    char *file_location_in = (char *)malloc(sizeof(char)*256);
    char *file_location_out = (char *)malloc(sizeof(char)*256);
    char *file_out = (char *)malloc(sizeof(char)*256);
    char *command = (char *)malloc(sizeof(char)*256);
    file_location_in = GetFileName(argv[0],DIR_INPUT);
    file_location_out = GetFileName(argv[0],DIR_OUT);
    file_out = GetFileName(argv[0],OUTPUT);
    FILE *file;
    file = fopen(file_location_in,"r");
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