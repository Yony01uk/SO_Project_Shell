#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "Parser_Variables.h"
#include <stdbool.h>
#include "ProcessStarter.h"
#include <ctype.h>

typedef struct command
{
    int iterator;
    int state_function;
    char *last_command;
    char **args;
    int arg_len;
} life_cycle;

life_cycle life;
void argument_detector(Parser_Variables parser)
{
    int init = life.iterator + 1;
    life.args = malloc(0);
    life.iterator += 1;
    while (life.iterator < parser.NewContractedForm_Lenght && (strcmp(parser.NewContractedForm[life.iterator], "&&") != 0 && strcmp(parser.NewContractedForm[life.iterator], "||") != 0 && strcmp(parser.NewContractedForm[life.iterator], "then") != 0 && strcmp(parser.NewContractedForm[life.iterator], "else") != 0 && strcmp(parser.NewContractedForm[life.iterator], ";") != 0 && strcmp(parser.NewContractedForm[life.iterator], "end") != 0 && strcmp(parser.NewContractedForm[life.iterator], "|") != 0 && strcmp(parser.NewContractedForm[life.iterator], ">") != 0 && strcmp(parser.NewContractedForm[life.iterator], ">>") != 0 && strcmp(parser.NewContractedForm[life.iterator], "<") != 0))
    {
        life.args = realloc(life.args, (life.iterator - init) + 1 * sizeof(char **)); // pick up all of the command's args
        life.args[life.iterator - init] = parser.NewContractedForm[life.iterator];
        life.iterator++;
    }
    life.arg_len = life.iterator - init;
    if (life.iterator != parser.NewContractedForm_Lenght - 1)
        life.iterator--;
}
bool change_output_command(Parser_Variables parser, char *command1_direction,char *id1, char *command1_args[],char *command2_direction,char *id2,char *command2_args[],char *dir_out,char *command2) // change output direction
{

    if ((strcmp(parser.NewContractedForm[life.iterator], "|") == 0 || strcmp(parser.NewContractedForm[life.iterator], ">") == 0 || strcmp(parser.NewContractedForm[life.iterator], ">>") == 0) && life.arg_len == 0) // if there are no args then it has an output
    {
        pid_t p = fork();
        if (p == 0)
        {
            Start(command1_args[0],command1_args[1],command1_args[2]);
            char *args[3] = {"","",""};
            if(strcmp(parser.NewContractedForm[life.iterator],"|") == 0)
            {
                Start(command2_args[0],command2_args[1],command2_args[2]);
                args[0] = strcpy(args[0],"pipe");
                args[1] = strcpy(args[1],id1);
                args[2] = strcpy(args[2],id2);
            }
            else if(strcmp(parser.NewContractedForm[life.iterator],">") == 0)
            {
                args[0] = strcpy(args[0],"l_a");
                args[1] = strcpy(args[1],id1);
                args[2] = strcpy(args[2],dir_out);
            }
            else
            {
                args[0] = strcpy(args[0],"d_l_a");
                args[1] = strcpy(args[1],id1);
                args[2] = strcpy(args[2],dir_out);
            }
            execv("./Outputs/outputsCommandsWorker",args);
            return true;
        }
        wait(&life.state_function);
        if(strcmp(parser.NewContractedForm[life.iterator],"|") == 0)
        {
            p = fork();
            if(p == 0)
            {
                execv(command1_direction,command1_args);
            }
            wait(&life.state_function);
            p = fork();
            if(p == 0)
            {
                if(IsUnknownCommand(command2) == -1)
                {
                    UnknownCommandsManager(id2,"NONE");
                }
                else
                {
                    execv(command2_direction,command2_args);
                }
            }
            wait(&life.state_function);
        }
        else
        {
            p = fork();
            if(p == 0)
            {
                execv(command1_direction,command1_args);
            }
            wait(&life.state_function);
        }
        return true;
    }
    return false;
}
void call_right_angular(Parser_Variables parser,char *id,char *file,char *command_location,char *command_args[])
{
    argument_detector(parser);
    pid_t p = fork();
    if (p == 0)
    {
        Start(command_args[0],command_args[1],command_args[2]);
        char *args[] = {"r_a",id,file};
        life.state_function = execv("./Outputs/outputsCommandsWorker",args);
        return;
    }
    wait(&life.state_function);
    pid_t p = fork();
    if (p == 0)
    {
        life.state_function = execv(command_location,command_args);
        return;
    }
    wait(&life.state_function);
}

char ** build_args(char *id,char *dir_in,char *dir_out,char *args[],int argc)
{
    char *args_result[argc + 3];
    args_result[0] = id;
    args_result[1] = dir_in;
    args_result[2] = dir_out;
    for(int i = 3; i < argc + 3; i++)
        args_result[i] = args[i - 3];
    return args_result;
}
char * get_command_direction(char *command)
{
    char *direction = (char *)malloc(sizeof(char)*256);
    direction = strcpy(direction,"./");
    if(IsUnknownCommand(command) == 0)
    {
        char *character = (char *)malloc(sizeof(char)*256);
        int c = toupper(command[0]);
        character = strchr(character,c);
        direction = strcat(direction,character);
        for(int i = 1; i < strlen(command); i++)
        {
            character = strchr(character,command[i]);
            direction = strcat(direction,character);
        }
        direction = strcat(direction,"_Command/");
        direction = strcat(direction,command);
        direction = strcat(direction,"CommandWorker");
        return direction;
    }
    return "NONE";
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