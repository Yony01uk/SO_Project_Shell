#include<sys/dir.h>
#include "../ProcessStarter.h"

#define Vars_Root "./Set_Command/Vars/"

char* ReadFile(FILE* file)
{
    char *data = (char *)malloc(sizeof(char)*256);
    char *temp = (char *)malloc(sizeof(char)*256);
    data = strcpy(data,"");
    int a = 1;
    while(!feof(file))
    {
        temp = fgets(temp,10000,file);
        data = strcat(data,temp);
    }
    return data;
}


char * setCommandWorkerWithArgs(char *name,char *value)
{
    char *location = (char *)malloc(sizeof(char)*256);
    location = strcpy(location,Vars_Root);
    location = strcat(location,name);
    location = strcat(location,".txt");
    FILE *var;
    if((var = fopen(location,"w")) == NULL)
    {
        creat(location,PERMS);
        var = fopen(location,"w");
    }
    fputs(value,var);
    fclose(var);
    return "NONE";    
}

char * setCommandWorkerWithOutArgs()
{
    char *location = (char *)malloc(sizeof(char)*256);
    location = strncpy(location,Vars_Root,strlen(Vars_Root) - 1);
    DIR *dir;
    dir = opendir(location);
    location = strcpy(location,Vars_Root);
    int a = 2;
    struct dirent *file;
    char *result = (char *)malloc(sizeof(char)*256);
    FILE *var_value;
    while((file = readdir(dir)) != NULL)
    {
        if(a == 0)
        {
            char *var_name = (char *)malloc(sizeof(char)*256);
            char *file_name = (char *)malloc(sizeof(char)*256);
            var_name = strncpy(var_name,file->d_name,strlen(file->d_name) - 4);
            result = strcat(result,var_name);
            file_name = strcpy(file_name,Vars_Root);
            file_name = strcat(file_name,file->d_name);
            var_value = fopen(file_name,"r");
            char *content = (char *)malloc(sizeof(char)*256);
            content = fgets(content,10000,var_value);
            result = strcat(result,": ");
            result = strcat(result,content);
            result = strcat(result,"\n");
            fclose(var_value);
            free(file_name);
            //free(var_name);
        }
        if(a > 0)
            a--;
    }
    closedir(dir);
    return result;
}

char *setCommandWorker(char *argv[])
{
    if(strcmp(argv[3],"NONE") == 0)
        return setCommandWorkerWithOutArgs();
    return setCommandWorkerWithArgs(argv[3],argv[4]);
}

void Tokenize(char *dest[],char *data,char *separator)
{
    int count = 0;
    for(int i = 0; i < strlen(data); i++)
    {
        if(data[i] == ' ')
        {
            count = i;
            dest[0] = strncpy(dest[0],data,count);
            break;
        }
    }
    data += count + 1;
    dest[1] = strcpy(dest[1],data);
}