#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/dir.h>

#define FILES_COMMANDS_INFO "Commands_Info"

char* ReadFile(FILE* file)
{
    char *data = (char *)malloc(sizeof(char)*256);
    char *tmp = (char *)malloc(sizeof(char)*256);
    fgets(data,100000,file);
    do
    {
        tmp = fgets(tmp,10000,file);
        data = strcat(data,tmp);
    }
    while(!feof(file));
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
        name = strncpy(name,file->d_name,strlen(file->d_name) - 4);
        if(strcmp(name,command) == 0)
        {
            char *file = (char *)malloc(sizeof(char)*256);
            file = strcat(root_to_info,command);
            file = strcat(file,".txt");
            FILE *file_to_open = fopen(file,"r");
            return ReadFile(file_to_open);
        }
    }
    free(root_to_info);
    return "NONE";
}