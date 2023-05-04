#include <ctype.h>
#include<unistd.h>
#include<sys/dir.h>
#include<sys/wait.h>
#include "parserWorker.h"

int LeftAngular(char *command_id,char *file)
{
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(command_id,DIR_OUT);
    FILE *f_out = fopen(file,"r");
    if(f_out == NULL)
        return -1;
    fclose(f_out);
    f_out = fopen(file_location,"w");
    fputs(file,f_out);
    fclose(f_out);
    return 0;
}

int DoubleLeftAngular(char *command_id,char *file)
{
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(command_id,DIR_OUT);
    FILE *f_out = fopen(file,"r");
    if(f_out == NULL)
        creat(file,PERMS);
    f_out = fopen(file_location,"w");
    fputs(file,f_out);
    fclose(f_out);
    return 0;
}

int RightAngular(char *command_id,char *file)
{
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(command_id,DIR_INPUT);
    FILE *f_out = fopen(file,"r");
    if(f_out == NULL)
        return -1;
    fclose(f_out);
    f_out = fopen(file_location,"w");
    fputs(file,f_out);
    fclose(f_out);
    return 0;
}

int Pipe(char *command_id_1,char *command_id_2)
{
    char *file_location1 = (char *)malloc(sizeof(char)*256);
    char *file_location2 = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    file_location1 = GetFileName(command_id_1,OUTPUT);
    file_location2 = GetFileName(command_id_2,DIR_INPUT);
    FILE *file;
    file = fopen(file_location2,"w");
    fputs(file_location1,file);
    fclose(file);
    return 0;
}

char* ReadFile(FILE* file)
{
    char *data = (char *)malloc(sizeof(char)*256);
    char *temp = (char *)malloc(sizeof(char)*256);
    data = strcpy(data,"");
    int a = 1;
    while(!feof(file))
    {
        if(a > 0)
        {
            a--;
        }
        else
        {
            data = strcat(data,temp);
        }
        temp = fgets(temp,10000,file);
    }
    return data;
}

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

int main(int argc,char *argv[])
{
    int init_command = 0;
    int end_command = 0;
    int redirection_index;
    int line_command = 1;
    int status = 0;
    while(end_command != argc)
    {
        int process = 1;
        end_command = MovePointer(init_command,argc,argv);
        char *current_command[end_command - init_command];
        for(int i = 0; i < end_command - init_command + 1; i++)
            current_command[i] = (char *)malloc(sizeof(char)*256);
        readCommandSection(init_command,end_command,argv,current_command);
        redirection_index = RedirectionIndex(end_command - init_command,current_command);
        char *in_command[redirection_index];
        for(int i =0; i < redirection_index; i++)
            in_command[i] = (char *)malloc(sizeof(char)*256);
        readCommandSection(0,redirection_index,current_command,in_command);
        if(redirection_index == end_command - init_command)
        {
            if(strcmp(in_command[0],"cd") == 0)
            {
                char* id = (char *)malloc(sizeof(char)*256);
                id = int_tostring(line_command);
                id = strcat(id,"_");
                id = strcat(id,int_tostring(process));
                char *args[] = {id,"NONE","NONE",in_command[1]};
                Start(args[0],args[1],args[2]);
                FILE *f_out = fopen(GetFileName(id,OUTPUT),"w");
                DIR *dir_to_open = opendir(args[3]);
                if(dir_to_open != NULL)
                {
                    char *dir =(char *)malloc(sizeof(char)*256);
                    dir = getcwd(dir,100000);
                    dir = strcat(dir,"/");
                    dir = strcat(dir,args[3]);
                    fputs(dir,f_out);
                    fclose(f_out);
                    closedir(dir_to_open);
                }
                else
                {
                    return -1;
                }
            }
            else if(strcmp(in_command[0],"help") == 0)
            {
                char *id = (char *)malloc(sizeof(char)*256);
                id = int_tostring(line_command);
                id = strcat(id,"_");
                id = strcat(id,int_tostring(process));
                char *args[] = {id,"NONE","NONE",""};
                if(redirection_index == 1)
                    args[3] = "help";
                else
                {
                    args[3] = (char *)malloc(sizeof(char)*256);
                    args[3] = strcpy(args[3],in_command[1]);
                }
                Start(args[0],args[1],args[2]);
                if(IsUnknownCommand(args[3]) == -1)
                {
                    char *new_arg = (char *)malloc(sizeof(char)*256);
                    new_arg = strcpy(new_arg,args[3]);
                    new_arg = strcat(new_arg," --help");
                    return UnknownCommandsManager(args[0],new_arg);
                }
                pid_t p;
                p = fork();
                if(p == 0)
                {
                    execv("./Help_Command/helpCommandWorker",args);
                }
                wait(&status);
                return status;
            }
            else if(strcmp(in_command[0],"history") == 0)
            {
                char *id = (char *)malloc(sizeof(char)*256);
                id = int_tostring(line_command);
                id = strcat(id,"_");
                id = strcat(id,int_tostring(process));
                char *args[] = {id,"NONE","NONE"};
                Start(args[0],args[1],args[2]);
                char *history = (char *)malloc(sizeof(char)*256);
                char *file_out = (char *)malloc(sizeof(char)*256);
                char *data = (char *)malloc(sizeof(char)*256);
                history = GetFileName("0_0",OUTPUT);
                file_out = GetFileName(id,OUTPUT);
                FILE *f_in = fopen(history,"r");
                FILE *f_out = fopen(file_out,"w");
                data = ReadFile(f_in);
                fclose(f_in);
                fputs(data,f_out);
                fclose(f_out);
            }
            else if(strcmp(in_command[0],"set") == 0)
            {
                char *id = (char *)malloc(sizeof(char)*256);
                id = int_tostring(line_command);
                id = strcat(id,"_");
                id = strcat(id,int_tostring(process));
                char *args[] = {id,"NONE","NONE","NONE","NONE"};
                Start(args[0],args[1],args[2]);
                if(redirection_index == 1)
                {
                    pid_t p;
                    p = fork();
                    if(p == 0)
                    {
                        execv("./Set_Command/setCommandWorker",args);
                    }
                    wait(&status);
                    return status;
                }
                else
                {
                    args[3] = in_command[1];
                    args[4] = in_command[2];
                    pid_t p;
                    p = fork();
                    if(p == 0)
                    {
                        execv("./Set_Command/setCommandWorker",args);
                    }
                    wait(&status);
                    return status;
                }
            }
            else if(strcmp(in_command[0],"get") == 0)
            {
                char *id = (char *)malloc(sizeof(char)*256);
                id = int_tostring(line_command);
                id = strcat(id,"_");
                id = strcat(id,int_tostring(process));
                char *args[] = {id,"NONE","NONE","NONE"};
                Start(id,"NONE","NONE");
                if(redirection_index > 1)
                {
                    args[3] = in_command[1];
                    pid_t p;
                    p = fork();
                    if(p == 0)
                    {
                        execv("./Get_Command/getCommandWorker",args);
                    }
                    wait(&status);
                }
                return status;
            }
            else if(strcmp(in_command[0],"unset") == 0)
            {
                char *id = (char *)malloc(sizeof(char)*256);
                id = int_tostring(line_command);
                id = strcat(id,"_");
                id = strcat(id,int_tostring(process));
                char *args[] = {id,"NONE","NONE","NONE"};
                Start(args[0],args[1],args[2]);
                if(redirection_index > 1)
                {
                    args[3] = in_command[1];
                }
                pid_t p;
                p = fork();
                if(p == 0)
                {
                    execv("./Unset_Command/unsetCommandWorker",args);
                }
                wait(&status);
                return status;
            }
            else if(strcmp(in_command[0],"exit") == 0)
            {
                return 1;
            }
            else
            {
                char *id = (char *)malloc(sizeof(char)*256);
                id = int_tostring(line_command);
                id = strcat(id,"_");
                id = strcat(id,int_tostring(process));
                char *args = (char *)malloc(sizeof(char)*256);
                args = strcpy(args,in_command[0]);
                for(int i = 1; i < redirection_index - 1; i++)
                {
                    args = strcat(args," ");
                    args = strcat(args,in_command[i]);
                }
                Start(id,"NONE","NONE");
                return UnknownCommandsManager(id,args);
            }
        }
        else
        {
            char *id = (char *)malloc(sizeof(char)*256);
            id = int_tostring(line_command);
            id = strcat(id,"_");
            id = strcat(id,int_tostring(process));
            Start(id,"NONE","NONE");
            process++;
            for(int i = init_command + redirection_index; i < end_command; i+= 2)
            {
                if(strcmp(argv[i],"|") == 0)
                {
                    char *new_id = (char *)malloc(sizeof(char)*256);
                    new_id = int_tostring(line_command);
                    new_id = strcat(new_id,"_");
                    new_id = strcat(new_id,int_tostring(process));
                    process++;
                    Start(new_id,"NONE","NONE");
                    int local_status = Pipe(id,new_id);
                }
            }
            if(strcmp(in_command[0],"cd") == 0)
            {
                char *args[] = {id,"NONE","NONE",in_command[1]};
                FILE *f_out = fopen(GetFileName(id,OUTPUT),"w");
                DIR *dir_to_open = opendir(args[3]);
                if(dir_to_open != NULL)
                {
                    char *dir =(char *)malloc(sizeof(char)*256);
                    dir = getcwd(dir,100000);
                    dir = strcat(dir,"/");
                    dir = strcat(dir,args[3]);
                    fputs(dir,f_out);
                    fclose(f_out);
                    closedir(dir_to_open);
                }
                else
                {
                    return -1;
                }
            }
            else if(strcmp(in_command[0],"help") == 0)
            {
                char *args[] = {id,"NONE","NONE",""};
                if(redirection_index == 1)
                    args[3] = "help";
                else
                {
                    args[3] = (char *)malloc(sizeof(char)*256);
                    args[3] = strcpy(args[3],in_command[1]);
                }
                if(IsUnknownCommand(args[3]) == -1)
                {
                    char *new_arg = (char *)malloc(sizeof(char)*256);
                    new_arg = strcpy(new_arg,args[3]);
                    new_arg = strcat(new_arg," --help");
                    int local_status = UnknownCommandsManager(args[0],new_arg);
                    if(local_status != 0)
                        return status;
                }
                pid_t p;
                p = fork();
                if(p == 0)
                {
                    execv("./Help_Command/helpCommandWorker",args);
                }
                wait(&status);
                if(status != 0)
                    return status;
            }
            else if(strcmp(in_command[0],"history") == 0)
            {
                char *args[] = {id,"NONE","NONE"};
                char *history = (char *)malloc(sizeof(char)*256);
                char *file_out = (char *)malloc(sizeof(char)*256);
                char *data = (char *)malloc(sizeof(char)*256);
                history = GetFileName("0_0",OUTPUT);
                file_out = GetFileName(id,OUTPUT);
                FILE *f_in = fopen(history,"r");
                FILE *f_out = fopen(file_out,"w");
                data = ReadFile(f_in);
                fclose(f_in);
                fputs(data,f_out);
                fclose(f_out);
            }
            else if(strcmp(in_command[0],"set") == 0)
            {
                char *args[] = {id,"NONE","NONE","NONE","NONE"};
                if(redirection_index == 1)
                {
                    pid_t p;
                    p = fork();
                    if(p == 0)
                    {
                        execv("./Set_Command/setCommandWorker",args);
                    }
                    wait(&status);
                    if(status != 0)
                        return status;
                }
                else
                {
                    args[3] = in_command[1];
                    args[4] = in_command[2];
                    pid_t p;
                    p = fork();
                    if(p == 0)
                    {
                        execv("./Set_Command/setCommandWorker",args);
                    }
                    wait(&status);
                    if(status != 0)
                        return status;
                }
            }
            else if(strcmp(in_command[0],"get") == 0)
            {
                char *args[] = {id,"NONE","NONE","NONE"};
                if(redirection_index > 1)
                {
                    args[3] = in_command[1];
                }
                pid_t p;
                p = fork();
                if(p == 0)
                {
                    execv("./Get_Command/getCommandWorker",args);
                }
                wait(&status);
                if(status != 0)
                    return status;
            }
            else if(strcmp(in_command[0],"unset") == 0)
            {
                char *args[] = {id,"NONE","NONE","NONE"};
                if(redirection_index > 1)
                {
                    args[3] = in_command[1];
                }
                pid_t p;
                p = fork();
                if(p == 0)
                {
                    execv("./Unset_Command/unsetCommandWorker",args);
                }
                wait(&status);
                if(status != 0)
                    return status;
            }
            else if(strcmp(in_command[0],"exit") == 0)
            {
                return 1;
            }
            else
            {
                char *args = (char *)malloc(sizeof(char)*256);
                args = strcpy(args,in_command[0]);
                for(int i = 1; i < redirection_index - 1; i++)
                {
                    args = strcat(args," ");
                    args = strcat(args,in_command[i]);
                }
                int local_status = UnknownCommandsManager(id,args);
                if(local_status != 0)
                    return local_status;
            }
            int aux_process = 2;
            for(int i = redirection_index + 1;i < end_command; i += 2)
            {
                char *aux_id = (char *)malloc(sizeof(char)*256);
                aux_id = int_tostring(line_command);
                aux_id = strcat(aux_id,"_");
                aux_id = strcat(aux_id,int_tostring(aux_process));
                aux_process++;
                char *args[] = {aux_id,"NONE","NONE","NONE"};
                if(strcmp(argv[i],"cd") == 0)
                {
                    char *args[] = {id,"NONE","NONE",in_command[1]};
                    FILE *f_out = fopen(GetFileName(id,OUTPUT),"w");
                    DIR *dir_to_open = opendir(args[3]);
                    if(dir_to_open != NULL)
                    {
                        char *dir =(char *)malloc(sizeof(char)*256);
                        dir = getcwd(dir,100000);
                        dir = strcat(dir,"/");
                        dir = strcat(dir,args[3]);
                        fputs(dir,f_out);
                        fclose(f_out);
                        closedir(dir_to_open);
                    }
                    else
                    {
                        return -1;
                    }
                }
                else if(strcmp(argv[i],"help") == 0)
                {
                    char *data_in = (char *)malloc(sizeof(char)*256);
                    char *args[] = {aux_id,"NONE","NONE","NONE"};
                    FILE *f_in = fopen(GetFileName(aux_id,DIR_INPUT),"r");
                    data_in = fgets(data_in,100000,f_in);
                    fclose(f_in);
                    f_in = fopen(data_in,"r");
                    data_in = fgets(data_in,100000,f_in);
                    fclose(f_in);
                    args[3] = data_in;
                    if(strcmp(data_in,"NONE") == 0)
                        args[3] = "help";
                    FILE *f = fopen("Prove.txt","w");
                    fputs(args[3],f);
                    fclose(f);
                    int done = 0;
                    if(IsUnknownCommand(args[3]) == -1)
                    {
                        char *new_arg = (char *)malloc(sizeof(char)*256);
                        new_arg = strcpy(new_arg,args[3]);
                        new_arg = strcat(new_arg," --help");
                        int local_status = UnknownCommandsManager(args[0],new_arg);
                        if(local_status != 0)
                            return local_status;
                        done = 1;
                    }
                    else if(done == 0)
                    {
                        pid_t p;
                        p = fork();
                        if(p == 0)
                        {
                            execv("./Help_Command/helpCommandWorker",args);
                        }
                        wait(&status);
                        if(status != 0)
                            return status;
                    }
                }
                else if(strcmp(argv[i],"history") == 0)
                {
                    char *args[] = {aux_id,"NONE","NONE"};
                    char *history = (char *)malloc(sizeof(char)*256);
                    char *file_out = (char *)malloc(sizeof(char)*256);
                    char *data = (char *)malloc(sizeof(char)*256);
                    history = GetFileName("0_0",OUTPUT);
                    file_out = GetFileName(aux_id,OUTPUT);
                    FILE *f_in = fopen(history,"r");
                    FILE *f_out = fopen(file_out,"w");
                    data = ReadFile(f_in);
                    fclose(f_in);
                    fputs(data,f_out);
                    fclose(f_out);
                }
                else if(strcmp(argv[i],"set") == 0)
                {
                    char *args[] = {aux_id,"NONE","NONE","NONE","NONE"};
                    pid_t p;
                    p = fork();
                    if(p == 0)
                    {
                        execv("./Set_Command/setCommandWorker",args);
                    }
                    wait(&status);
                    if(status != 0)
                        return status;
                }
                else if(strcmp(argv[i],"get") == 0)
                {
                    char *args[] = {aux_id,"NONE","NONE","NONE"};
                    if(redirection_index > 1)
                    {
                        args[3] = in_command[1];
                        pid_t p;
                        p = fork();
                        if(p == 0)
                        {
                            execv("./Get_Command/getCommandWorker",args);
                        }
                        wait(&status);
                    }
                    return status;
                }
                else if(strcmp(argv[i],"unset") == 0)
                {
                    char *args[] = {aux_id,"NONE","NONE","NONE"};
                    if(redirection_index > 1)
                    {
                        args[3] = in_command[1];
                    }
                    pid_t p;
                    p = fork();
                    if(p == 0)
                    {
                        execv("./Unset_Command/unsetCommandWorker",args);
                    }
                    wait(&status);
                    return status;
                }
                else if(strcmp(argv[i],"exit") == 0)
                {
                    return 1;
                }
                else
                {
                    char *args = (char *)malloc(sizeof(char)*256);
                    args = strcpy(args,argv[i]);
                    return UnknownCommandsManager(aux_id,args);
                }
    
            }
        }
        init_command = end_command + 1;
        line_command++;
    }
}