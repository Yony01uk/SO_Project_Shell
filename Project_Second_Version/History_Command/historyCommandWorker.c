#include <stdlib.h>
#include<unistd.h>
#include "historyWorker.h"

//deben existir al menos 2 elementos en *argv[]
int main(int argc,char *argv[])
{
    for(int i = 0; i < argc; i++)
        printf("%s\n",argv[i]);
    char *command = (char *)malloc(sizeof(char)*256);
    for(int i = 1; i < argc; i++)
    {
        if(i == 1)
            command = strcpy(command,argv[i]);
        else
        {
            command = strcat(command," ");
            command = strcat(command,argv[i]);
        }
    }
    historyCommandWorker(command);
}