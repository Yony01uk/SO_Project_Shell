#include<sys/wait.h>
#include<unistd.h>
#include "ProcessStarter.h"

int UnknownCommandsManager(char *id_command,char *arg)
{
    char *data = (char *)malloc(sizeof(char)*256);
    char *file_location_in = (char *)malloc(sizeof(char)*256);
    char *file_location_out = (char *)malloc(sizeof(char)*256);
    char *file_out = (char *)malloc(sizeof(char)*256);
    char *command_content = (char *)malloc(sizeof(char)*256);
    file_location_in = GetFileName(id_command,DIR_INPUT);
    file_location_out = GetFileName(id_command,DIR_OUT);
    file_out = GetFileName(id_command,OUTPUT);
    FILE *command;
    command = fopen(file_location_in,"r");
    data = fgets(data,100000,command);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(command);
        command = popen(arg,"r");
    }
    else
    {
        fclose(command);
        command = fopen(data,"r");
        data = fgets(data,sizeof(data),command);
        char *temp = (char *)malloc(sizeof(char)*256);
        while(!feof(command))
        {
            temp = fgets(temp,sizeof(temp),command);
            data = strcat(data,temp);
        }
        fclose(command);
        command = popen(data,"r");
    }
    FILE *f_out = fopen(file_location_out,"r");
    data = fgets(data,sizeof(data),f_out);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(f_out);
        f_out = fopen(file_out,"w");
        char *copy = (char *)malloc(sizeof(char)*256);
        int start = 0;
        while(!feof(command))
        {
            if(start == 0)
                start++;
            else
            {
                copy = strcpy(copy,data);
                fputs(copy,f_out);
            }
            data = fgets(data,sizeof(data),command);
        }
        fclose(f_out);
        pclose(command);
    }
    else
    {
        fclose(f_out);
        f_out = fopen(data,"w");
        while(!feof(command))
        {
            data = fgets(data,sizeof(data),command);
            fputs(data,f_out);
        }
        fclose(f_out);
        pclose(command);
    }
}

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

int main()
{
    char *args1[] = {"0","NONE","NONE","yonyuk","esto funciona pinga"};
    char *args2[] = {"1","NONE","NONE","nano","y esto tambien"};
    char *args[] = {"pipe","0","1"};
    int pid;
    int status;
    // Start(args1[0],args1[1],args1[2]);
    Start(args2[0],args2[1],args2[2]);
    //UnknownCommandsManager(args);
    if(IsUnknownCommand(args2[3]) == -1)
    {
        char *arg[] = {"100","NONE","NONE",""};
        Start(arg[0],arg[1],arg[2]);
        char *a = (char *)malloc(sizeof(char)*256);
        a = strcpy(a,args2[3]);
        a = strcat(a," --help");
        arg[3] = a;
        UnknownCommandsManager(arg[0],a); 
    }   
    pid = fork();
    execv("./Help_Command/helpCommandWorker",args2);
    // pid =fork();
    // execv("./Set_Command/setCommandWorker",args2);
    // pid = fork();
    // execv("./Outputs/outputsCommandsWorker",args);
}