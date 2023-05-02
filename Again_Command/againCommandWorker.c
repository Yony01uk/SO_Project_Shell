#include "againCommand.h"

int main(int argc, char *argv[])
{
    char *command = (char *)malloc(sizeof(char)*256);
    int id;
    FILE *file;
    char *file_location_in = (char *)malloc(sizeof(char)*256);
    char *file_location_out = (char *)malloc(sizeof(char)*256);
    char *file_out = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    file_location_in = GetFileName(argv[0],DIR_INPUT);
    file_location_out = GetFileName(argv[0],DIR_OUT);
    file_out = GetFileName(argv[0],OUTPUT);
    file = fopen(file_location_in,"r");
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
    file = fopen(file_location_out,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        file = fopen(file_out,"w");
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
