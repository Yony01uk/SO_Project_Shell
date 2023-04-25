#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>

#define HISTORY_FILE "/media/yonatan01/1602CB9502CB77EF/University/3er/SOperativo/Project_Second_Version/History_Command/History.txt"
#define COMMANDS_COUNT 10

char *SearchCommand(int command)
{
    FILE *file_to_open;
    file_to_open = fopen(HISTORY_FILE,"r");
    int count = COMMANDS_COUNT + 1;
    char *command_found;
    command_found = (char *)malloc(sizeof(char)*256);
    while(!feof(file_to_open))
    {
        command_found = fgets(command_found,100000,file_to_open);
        count--;
        if(count == command)
        {
            command_found = strncpy(command_found,command_found,strlen(command_found) - 1);
            return command_found;
        }
    }
    command_found = "No se puede encontrar el comando solicitado";
    return command_found;
}