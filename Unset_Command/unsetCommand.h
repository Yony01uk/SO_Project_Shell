#include<fcntl.h>
#include "../ProcessStarter.h"

#define Vars_Root "./Set_Command/Vars/"

char * unsetCommandWorker(char *name)
{
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = strcpy(file_location,Vars_Root);
    file_location = strcat(file_location,name);
    file_location = strcat(file_location,".txt");
    FILE *file = fopen(file_location,"r");
    if(file == NULL)
        return "FAIL";
    fclose(file);
    remove(file_location);
    return "SUCCES";
}