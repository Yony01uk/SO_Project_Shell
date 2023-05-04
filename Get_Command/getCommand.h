#include "../ProcessStarter.h"

#define VARS_ROOT "./Set_Command/Vars"

char * getCommandWorker(char *name)
{
    if(strcmp(name,"NONE") == 0)
        return "NONE";
    char *file_name = (char *)malloc(sizeof(char)*256);
    file_name = strcpy(file_name,VARS_ROOT);
    file_name = strcat(file_name,"/");
    file_name = strcat(file_name,name);
    file_name = strcat(file_name,".txt");
    FILE *file = fopen(file_name,"r");
    char *content = (char *)malloc(sizeof(char)*256);
    content = fgets(content,10000,file);
    fclose(file);
    return content;
}