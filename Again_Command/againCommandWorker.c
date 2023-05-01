#include "againCommand.h"

int main(int argc, char *argv[])
{
    Start(argv[0],argv[1],argv[2]);
    char *command = (char *)malloc(sizeof(char)*256);
    int id;
    FILE *file;
    char *file_location = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(argv[0],DIR_INPUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        id = atoi(argv[3]);
    }
    else
    {
        fclose(file);
        file = fopen(data,"r");
        data = fgets(data,10000,file);
        fclose(file);
        id = atoi(data);
    }
    command = SearchCommand(id);
    file_location = GetFileName(argv[0],DIR_OUT);
    file = fopen(file_location,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        file_location = GetFileName(argv[0],OUTPUT);
        fclose(file);
        file = fopen(file_location,"w");
        fputs(command,file);
        fclose(file);
    }
    else
    {
        fclose(file);
        file = fopen(data,"w");
        fputs(command,file);
        fclose(file);
    }
}
