#include "/media/yonatan01/1602CB9502CB77EF/University/3er/SOperativo/Project_Second_Version/ProcessStarter.h"

int IsUnknownCommand(char *command)
{
    FILE *commands = fopen("CommandsList.txt","r");
    char *data = (char *)malloc(sizeof(char)*256);
    while(!feof(commands))
    {
        data = fgets(data,10000,commands);
        if(strlen(data) - 1 == strlen(command))
            if(strncmp(command,data,strlen(command)) == 0)
                return 0;
    }
    return -1;
}