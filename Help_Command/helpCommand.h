#include "../ProcessStarter.h"
#include<sys/dir.h>
#include<unistd.h>

#define FILES_COMMANDS_INFO "./Help_Command/Commands_Info"

char* ReadFile(FILE* file)
{
    char *data = (char *)malloc(sizeof(char)*256);
    char *tmp = (char *)malloc(sizeof(char)*256);
    while(!feof(file))
    {
        tmp = fgets(tmp,10000,file);
        data = strcat(data,tmp);
    }
    return data;
}

char * helpCommandWorker(char *command)
{
    char *root_to_info = (char *)malloc(sizeof(char)*256);
    root_to_info = strcpy(root_to_info,FILES_COMMANDS_INFO);
    root_to_info = strcat(root_to_info,"/");
    DIR *dir_to_open;
    dir_to_open = opendir(FILES_COMMANDS_INFO);
    struct dirent *file;
    int a = 2;
    while((file = readdir(dir_to_open)) != NULL)
    {
        if(a > 0)
        {
            a--;
            continue;
        }
        char *name = (char *)malloc(sizeof(char)*256);
        name = strcpy(name,command);
        name = strcat(name,".txt");
        if(strcmp(name,file->d_name) == 0)
        {
            char *file = (char *)malloc(sizeof(char)*256);
            file = strcat(root_to_info,name);
            FILE *file_to_open = fopen(file,"r");
            return ReadFile(file_to_open);
        }
    }
    free(root_to_info);
    return "NONE";
}