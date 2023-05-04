#include "input.h"
#include "Operation.h"
#include "Parser.h"
/////////////////////////////
// gcc shell.c -o output
int get_started(char *);
char *GetFileName(char *id, int output) {}
char **comillas_set(char **args, int lenght)
{
    char **output = malloc(0);
    char *input;
    for (int i = 1; i < lenght; i++) // put off "comilla"
    {
        strcat(input, " ");
        strcat(input, args[i]);
    }
    get_started(input);                             // call command line input
    char *path = GetFileName(life.last_command, 0); // output of last_command

    FILE *f = fopen(path, "r");
    int output_lenght = 0;

    while (!feof(f)) // read the file
    {
        char *aux = malloc(0);
        char c;
        while (c != '\n')
        {
            aux = realloc(aux, 1);
            c = fgetc(f);
            aux[strlen(aux) - 1] = c;
            fseek(f, 1, ftell(f));
        }
        output = realloc((char *)output, 1);
        output_lenght++;
        output[output_lenght - 1] = aux;
    }
    return output;
}
int get_started(char *input)
{
    Parser_Variables parser;
    parser.StringLenght = strlen(input);
    sub_process.numberChilds = 0;

    int num_cmd = 0;
    parser = ToParse(input, parser);
    if (parser.NewContractedForm == NULL)
    {
        life.state_function = -1;
        return 0;
    }
    // #HASTAG FUNCTION
    tuple hasTag = hastag(parser.NewContractedForm, parser.NewContractedForm_Lenght);
    parser.NewContractedForm = hasTag.new_input;
    parser.NewContractedForm_Lenght = hasTag.new_inputLenght;
    //& BACKGROUND FUNCTION
    OnGoing = ampersand(parser.NewContractedForm, parser.NewContractedForm_Lenght, OnGoing);
    parser.NewContractedForm = OnGoing.new_input;
    parser.NewContractedForm_Lenght = OnGoing.new_inputLenght;

    bool under_if = false;
    for (int i = 0; i < parser.NewContractedForm_Lenght; i++)
    {
        life.iterator=i;
        if (life.state_function != 0 && under_if == false)
            return 0;

        kill_zombies(sub_process.numberChilds, sub_process.childs); // kill posible zombies

        if (strcmp(parser.NewContractedForm[i], "if") == 0)
        {
            under_if = true;
        }
        if (strcmp(parser.NewContractedForm[i], "then") == 0)
        {
            int if_found = 1;
            if (life.state_function != 0)
            {
                int then_found = 1;
                int end_found = 0;
                while (!(if_found - then_found == 0 && then_found - end_found == 0) && i < parser.NewContractedForm_Lenght)
                {
                    i++;
                    if (strcmp(parser.NewContractedForm[i], "if") == 0)
                        if_found++;
                    if (strcmp(parser.NewContractedForm[i], "then") == 0)
                        then_found++;
                    if (strcmp(parser.NewContractedForm[i], "end") == 0)
                        end_found++;
                    if (strcmp(parser.NewContractedForm[i], "else") == 0 && then_found - end_found == 1)
                        break;
                }
                life.state_function = 0;
            }
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "else") == 0)
        {
            int if_found = 1;
            int then_found = 1;
            int end_found = 0;
            while (!(if_found - then_found == 0 && then_found - end_found == 0) && i < parser.NewContractedForm_Lenght)
            {
                i++;
                if (strcmp(parser.NewContractedForm[i], "if") == 0)
                    if_found++;
                if (strcmp(parser.NewContractedForm[i], "then") == 0)
                    then_found++;
                if (strcmp(parser.NewContractedForm[i], "end") == 0)
                    end_found++;
            }
            life.state_function = 0;
        }
        if (strcmp(parser.NewContractedForm[i], "&&") == 0 || strcmp(parser.NewContractedForm[i], "||") == 0) // and operator
        {
            if (life.state_function != 0 && strcmp(parser.NewContractedForm[i], "&&") == 0) // for && operator, if state is not 0 then command besides right is not executed
            {
                i++;
                while (i < parser.NewContractedForm_Lenght && (strcmp(parser.NewContractedForm[i], "&&") != 0 && strcmp(parser.NewContractedForm[i], "||") != 0 && strcmp(parser.NewContractedForm[i], "then") != 0 && strcmp(parser.NewContractedForm[i], "else") != 0 && strcmp(parser.NewContractedForm[i], ";") != 0 && strcmp(parser.NewContractedForm[i], "end") != 0 && strcmp(parser.NewContractedForm[i], "|") != 0 && strcmp(parser.NewContractedForm[i], ">") != 0 && strcmp(parser.NewContractedForm[i], ">>") != 0 && strcmp(parser.NewContractedForm[i], "<") != 0))
                {
                    i++; // dismise args of command
                }
                i--; // we need this iteration in case we are inside an if statementor next are &&,|| operators
                life.state_function = 0;
                goto D;
            }
            if (life.state_function == 0 && strcmp(parser.NewContractedForm[i], "||") == 0) // for && operator, if state is 0 then command besides right is not executed
            {
                i++;
                while (i < parser.NewContractedForm_Lenght && (strcmp(parser.NewContractedForm[i], "&&") != 0 && strcmp(parser.NewContractedForm[i], "||") != 0 && strcmp(parser.NewContractedForm[i], "then") != 0 && strcmp(parser.NewContractedForm[i], "else") != 0 && strcmp(parser.NewContractedForm[i], ";") != 0 && strcmp(parser.NewContractedForm[i], "end") != 0 && strcmp(parser.NewContractedForm[i], "|") != 0 && strcmp(parser.NewContractedForm[i], ">") != 0 && strcmp(parser.NewContractedForm[i], ">>") != 0 && strcmp(parser.NewContractedForm[i], "<") != 0))
                {
                    i++; // dimise args of command
                }
                i--; // we need this iteration in case we are inside an if statementor next are &&,|| operators
                life.state_function = 0;
                goto D;
            }
            int init = i + 1;
            char *command = parser.NewContractedForm[init];
            if (!IsCommand(command))
            {
                printf("%s is not a command", command);
                life.state_function = -1;
                i++;
                goto D;
            }
            char **args = malloc(0);
            i += 2;
            while (i < parser.NewContractedForm_Lenght && (strcmp(parser.NewContractedForm[i], "&&") != 0 && strcmp(parser.NewContractedForm[i], "||") != 0 && strcmp(parser.NewContractedForm[i], "then") != 0 && strcmp(parser.NewContractedForm[i], "else") != 0 && strcmp(parser.NewContractedForm[i], ";") != 0 && strcmp(parser.NewContractedForm[i], "end") != 0 && strcmp(parser.NewContractedForm[i], "|") != 0 && strcmp(parser.NewContractedForm[i], ">") != 0 && strcmp(parser.NewContractedForm[i], ">>") != 0 && strcmp(parser.NewContractedForm[i], "<") != 0))
            {
                args = realloc(args, (i - init) * sizeof(char **));
                args[i - init - 1] = parser.NewContractedForm[i];
                i++;
            }
            i--; // we need this iteration in case we are inside an if statement or next are &&,|| operators
            // call function command with arguments "args"
            // update state_function
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "end") == 0)
        {
            under_if = false;
            life.state_function = 0;
        }
        if (strcmp(parser.NewContractedForm[i], "cd") == 0) // function cd
        {
            if (strcmp(parser.NewContractedForm[i + 1], "<") == 0)
            {
                // call command with parser.NewContractedForm[i+2] arg
                i += 2;
                goto D;
            }
            int init = i + 1;
            char **args = malloc(0);
            i += 1;
            while (i < parser.NewContractedForm_Lenght && (strcmp(parser.NewContractedForm[i], "&&") != 0 && strcmp(parser.NewContractedForm[i], "||") != 0 && strcmp(parser.NewContractedForm[i], "then") != 0 && strcmp(parser.NewContractedForm[i], "else") != 0 && strcmp(parser.NewContractedForm[i], ";") != 0 && strcmp(parser.NewContractedForm[i], "end") != 0 && strcmp(parser.NewContractedForm[i], "|") != 0 && strcmp(parser.NewContractedForm[i], ">") != 0 && strcmp(parser.NewContractedForm[i], ">>") != 0 && strcmp(parser.NewContractedForm[i], "<") != 0))
            {
                args = realloc(args, (i - init + 1) * sizeof(char **)); // pick up all of the command's args
                char *o = parser.NewContractedForm[i];
                args[i - init] = parser.NewContractedForm[i];
                i++;
            }
            if (i != parser.NewContractedForm_Lenght - 1)
                i--;
            // no output
            /*state_function=; call set function*/
            num_cmd++;
            life.last_command = process_id(num_cmd, getpid());
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "true") == 0)
        {
            life.state_function = 0;
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "false") == 0)
        {
            life.state_function = -1;
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "jobs") == 0) // function jobs
        {
            life.last_command = "jobs";
            for (int j = 0; j < sub_process.numberChilds; j++)
            {
                printf("\n[%d] pid:%d", j, sub_process.childs[j]);
            }
            if (strcmp(parser.NewContractedForm[i], "|") == 0 || strcmp(parser.NewContractedForm[i], ">") == 0 && strcmp(parser.NewContractedForm[i], ">>") == 0)
            {
                // change output direction
                // call command but no printing
                i--;
                goto D;
            }
            num_cmd++;
            life.last_command = process_id(num_cmd, getpid());
            life.state_function = 0;
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "fg") == 0) // function fg
        {
            if (strcmp(parser.NewContractedForm[i + 1], "<") == 0)
            {
                // call command with parser.NewContractedForm[i + 2] arg
                i += 2;
                goto D;
            }
            // if (i + 1 < parser.NewContractedForm_Lenght)
            //     fg(atoi(parser.NewContractedForm[i + 1]));
            // i++;
            num_cmd++;
            life.last_command = process_id(num_cmd, getpid());
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], ";") == 0) // pass to the next instruction
        {
            life.state_function = 0;
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "set") == 0)
        {
            if (strcmp(parser.NewContractedForm[i + 2], "<") == 0)
            {
                i += 2;
                call_left_angular(parser, "./Set_Command/setCommandWorker");
                i = life.iterator;
                goto D;
            }
            int init = i + 1;
            argument_detector(parser);

            char **comillas; // verify if there are "comillas"
            bool comillas_flag = false;
            if (life.iterator - init > 3 && life.args[1][0] == '`' && life.args[life.iterator][strlen(life.args[life.iterator]) - 1] == '`')
            {
                life.args[1][0] = ' ';
                life.args[life.iterator][strlen(life.args[life.iterator]) - 1] = ' ';
                comillas = comillas_set(life.args, life.iterator - init);
                comillas_flag = true;
            }
            else if (life.iterator - init == 0)
            {
                goto E;
            }
            if (comillas_flag = true)
            {
                char *arg[] = {life.last_command, "NONE", "NONE", "NONE"};
                pid_t p = fork();
                if (p == 0)
                {
                    life.state_function = execv("./Set_Command/setCommandWorker", arg);
                    return life.state_function;
                }
                wait(&life.state_function);

                goto D;
            }
            else
            {
                char *arg[] = {life.last_command, "NONE", "NONE", "NONE"};
                pid_t p = fork();
                if (p == 0)
                {
                    life.state_function = execv("./Set_Command/setCommandWorker", arg);
                    return life.state_function;
                }
                wait(&life.state_function);
                goto D;
            }
        E:
            char *arg[] = {life.last_command, "NONE", "NONE", "NONE"};
            change_output_command(parser, init, "./Set_Command/setCommandWorker", arg);
            // call Start()
            pid_t p = fork();
            if (p == 0)
            {
                char **args;
                life.state_function = execv("./Set_Command/setCommandWorker", arg);
                return life.state_function;
            }
            wait(&life.state_function);

            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "unset") == 0)
        {
            char *command_direction = "./Unset_Command/unsetCommandWorker";
            num_cmd++;
            char *id = process_id(num_cmd, getpid());
            char *command_args[] = {"","","",""};
            command_args[0] = strcpy(command_args[0],id);
            command_args[1] = strcpy(command_args[1],"NONE");
            command_args[2] = strcpy(command_args[2],"NONE");
            Start(command_args[0],command_args[1],command_args[2]);
            if(i + 1 < parser.NewContractedForm_Lenght)
            {
                command_args[3] = parser.NewContractedForm[i + 1];
            }
            if (strcmp(parser.NewContractedForm[i + 1], "<") == 0)
            {
                // call command with parser.NewContractedForm[i+2] arg
                call_right_angular(parser,id,parser.NewContractedForm[i + 2],command_direction,command_args);
                i += 2;
                goto D;
            }
            pid_t p = fork();
            if(p == 0)
            {
                life.state_function = execv(command_direction,command_args);
            }
            wait(&life.state_function);
            life.last_command = id;
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "get") == 0)
        {
            char *command_direction = "./Get_Command/getCommandWorker";
            num_cmd++;
            char *id = process_id(num_cmd, getpid());
            char *command_args[] = {"","","",""};
            command_args[0] = strcpy(command_args[0],id);
            command_args[1] = strcpy(command_args[1],"NONE");
            command_args[2] = strcpy(command_args[2],"NONE");
            Start(command_args[0],command_args[1],command_args[2]);
            if(i + 1 < parser.NewContractedForm_Lenght)
            {
                command_args[3] = parser.NewContractedForm[i + 1];
            }
            if (strcmp(parser.NewContractedForm[i + 1], "<") == 0)
            {
                // call command with parser.NewContractedForm[i+2] arg
                call_right_angular(parser,id,parser.NewContractedForm[i + 2],command_direction,command_args);
                i += 2;
                goto D;
            }
            pid_t p = fork();
            if(p == 0)
            {
                life.state_function = execv(command_direction,command_args);
            }
            wait(&life.state_function);
            life.last_command = id;
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "help") == 0)
        {
            char *command_direction = "./Help_Command/helpCommandWorker";
            num_cmd++;
            char *id = process_id(num_cmd, getpid());
            char *command_args[] = {"","","",""};
            command_args[0] = strcpy(command_args[0],id);
            command_args[1] = strcpy(command_args[1],"NONE");
            command_args[2] = strcpy(command_args[2],"NONE");
            Start(command_args[0],command_args[1],command_args[2]);
            argument_detector(parser);
            pid_t p;
            if(life.arg_len == 0)
            {
                command_args[3] = strcpy(command_args[3],"help");
                p = fork();
                if(p == 0)
                {
                    life.state_function = execv(command_direction,command_args);
                    return life.state_function;
                }
                wait(&life.state_function);
                goto D;
            }
            else
            {
                command_args[3] = strcpy(command_args[3],parser.NewContractedForm[i + 1]);
                p = fork();
                if(p == 0)
                {
                    life.state_function = execv(command_direction,command_args);
                    return life.state_function;
                }
                wait(&life.state_function);
                goto D;
            }
            if (strcmp(parser.NewContractedForm[i + 1], "<") == 0)
            {
                // call command with parser.NewContractedForm[i+2] arg
                call_right_angular(parser,id,parser.NewContractedForm[i + 2],command_direction,command_args);
                i += 2;
                goto D;
            }
            //falta por analizar el caso en que haya redireccion de salida
        }
        if (strcmp(parser.NewContractedForm[i], "again") == 0)
        {
            pid_t p;
            num_cmd++;
            char *id = process_id(num_cmd,getpid());
            char *command_args[] = {"","","",""};
            char *command_direction = "./Again_Command/againCommandWorker";
            command_args[0] = strcpy(command_args[0],id);
            command_args[1] = strcpy(command_args[1],"NONE");
            command_args[2] = strcpy(command_args[2],"NONE");
            command_args[3] = strcpy(command_args[3],parser.NewContractedForm[i + 1]);
            Start(command_args[0],command_args[1],command_args[2]);
            if(strcmp(parser.NewContractedForm[i + 1],"<") == 0)
            {
                call_right_angular(parser,id,parser.NewContractedForm[i + 2],command_direction,command_args);
                life.last_command = id;
            }
            else if(strcmp(parser.NewContractedForm[i + 1],"|") == 0)
            {
                num_cmd++;
                char *id1 = process_id(num_cmd,getpid());
                char *command2_args[] = {"","","",""};
                command2_args[0] = strcpy(command2_args[0],id);
                command2_args[1] = strcpy(command2_args[1],"NONE");
                command2_args[2] = strcpy(command2_args[2],"NONE");
                command2_args[3] = strcpy(command2_args[3],"NONE");
                char *command_direction = get_command_direction(parser.NewContractedForm[i + 2]);
                change_output_command(parser,command_direction,id,command_args,get_command_direction(parser.NewContractedForm[i + 2]),id1,command2_args,"NONE",parser.NewContractedForm[i + 2]);
            }
            else if(strcmp(parser.NewContractedForm[i + 1],""))
            {

            }
            else
            {
                p = fork();
                if(p == 0)
                {
                    life.state_function = execv(command_direction,command_args);
                    return life.state_function;
                }
                wait(&life.state_function);
            }
            char *file_info = (char *)malloc(sizeof(char)*256);
            file_info = GetFileName(id,DIR_OUT);
            FILE *f_out = fopen(file_info,"r");
            char *data =(char *)malloc(sizeof(char)*256);
            data = fgets(data,100000,f_out);
            if(strcmp(data,"NONE") == 0)
            {
                fclose(f_out);
                file_info = GetFileName(id,OUTPUT);
                f_out = fopen(file_info,"r");
                data = fgets(data,100000,f_out);
                life.state_function = get_started(data);
            }
            else
            {
                fclose(f_out);
                f_out = fopen(data,"r");
                data = fgets(data,100000,f_out);
                life.state_function = get_started(data);
            }
            life.last_command = id;
            goto D;
        }
        if (strcmp(parser.NewContractedForm[i], "history") == 0) // history command
        {
            // call history command
            //  state_function =;
            num_cmd++;
            life.last_command = process_id(num_cmd, getpid());
            goto D;
        }
        // at this point it's asumed that next lines are linux command till a curt operator
        if (strcmp(parser.NewContractedForm[i + 1], "<") == 0)
        {
            // change input direction
            //  call command with parser.NewContractedForm[i+1] arg
            num_cmd++;
            life.last_command = process_id(num_cmd, getpid());
            i += 1;
            goto D;
        }
        char *command = parser.NewContractedForm[i];
        char **args = malloc(0);
        int init = i + 1;
        i += 2;
        while (i < parser.NewContractedForm_Lenght && (strcmp(parser.NewContractedForm[i], "&&") != 0 && strcmp(parser.NewContractedForm[i], "||") != 0 && strcmp(parser.NewContractedForm[i], "then") != 0 && strcmp(parser.NewContractedForm[i], "else") != 0 && strcmp(parser.NewContractedForm[i], ";") != 0 && strcmp(parser.NewContractedForm[i], "end") != 0 && strcmp(parser.NewContractedForm[i], "|") != 0 && strcmp(parser.NewContractedForm[i], ">") != 0 && strcmp(parser.NewContractedForm[i], ">>") != 0 && strcmp(parser.NewContractedForm[i], "<") != 0))
        {
            args = realloc(args, (i - init) * sizeof(char **)); // pick up all of the command's args
            args[i - init - 1] = parser.NewContractedForm[i];
            i++;
        }
        if (i != parser.NewContractedForm_Lenght - 1)
            i--;
        else
            goto D;
        //ask for output re-direction
        life.state_function = execvp(command, args);
        if (life.state_function != 0)
            printf("\n%s :is not a command", command);
        else
        {
            num_cmd++;
            life.last_command = process_id(num_cmd, getpid());
        }
    D:
    }
    return 0;
}
int main()
{
    signal(SIGINT, signalFunction);
    printf("my-Prompt $ ");
    // char *input = InputX();
    char *input = "history && cd /home/ & cd /home/";

    while (Exit(input) == false)
    {
        get_started(input);
        kill_zombies(sub_process.numberChilds, sub_process.childs);
        printf("\nmy-Prompt $ ");
        if (OnGoing.forkedToKill == true)
            return 0;
        // call history in input
    C:
        input = InputX();
        life.state_function = 0;
        int len = strlen(input);
        if (len == 0)
            goto C;
    }
    return 0;
}
///////////////////////////