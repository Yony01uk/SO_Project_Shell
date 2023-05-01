#include "CommandsManager.h"

int main(int argc,char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char output[1024];
    char *data = (char *)malloc(sizeof(char)*256);
    char *file_location = (char *)malloc(sizeof(char)*256);
    char *command_content = (char *)malloc(sizeof(char)*256);
    FILE *command;
    file_location = GetFileName(argv[0],DIR_INPUT);
    command = fopen(file_location,"r");
    data = fgets(data,sizeof(data),command);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(command);
        command = popen(argv[3],"r");
    }
    else
    {
        fclose(command);
        command = fopen(data,"r");
        data = fgets(data,sizeof(data),command);
        char *temp = (char *)malloc(sizeof(char)*256);
        while(!feof(command))
        {
            temp = fgets(temp,sizeof(temp),command);
            data = strcat(data,temp);
        }
        fclose(command);
        command = popen(data,"r");
    }
    file_location = GetFileName(argv[0],DIR_OUT);
    FILE *f_out = fopen(file_location,"r");
    data = fgets(data,sizeof(data),f_out);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(f_out);
        file_location = GetFileName(argv[0],OUTPUT);
        f_out = fopen(file_location,"w");
        while(!feof(command))
        {
            data = fgets(data,sizeof(data),command);
            fputs(data,f_out);
        }
        fclose(f_out);
        pclose(command);
    }
    else
    {
        fclose(f_out);
        f_out = fopen(data,"w");
        while(!feof(command))
        {
            data = fgets(data,sizeof(data),command);
            fputs(data,f_out);
        }
        fclose(f_out);
        pclose(command);
    }
}   