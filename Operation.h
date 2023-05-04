#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
typedef struct
{
    char **new_input;
    int new_inputLenght;
    bool *printing;
    bool forkedToKill;
} tuple;
tuple OnGoing;
typedef struct
{
    __pid_t *childs;
    int numberChilds;
} process;
process sub_process;

bool Exit(char *input)
{
    const char exit[] = "exit";
    if (strlen(input) < 4)
        return false;

    for (int i = 0; i < 4; i++)
    {
        if (*(input + i) != exit[i])
            return false;
    }
    return true;
}
tuple hastag(char **input, int lenght)
{
    tuple t;
    char **noHastag = malloc(0);
    int new_Lenght = 0;
    for (int i = 0; i < lenght; i++)
    {
        if (*(input[i]) == '#')
            break;
        new_Lenght = i;
        noHastag = realloc(noHastag, (i + 1) * sizeof(char *));
        noHastag[new_Lenght] = malloc(strlen(input[i]));
        strcpy(noHastag[i], input[i]);
    }
    t.new_input = noHastag;
    t.new_inputLenght = new_Lenght + 1;
    return t;
}
tuple ampersand(char **input, int lenght, tuple OnGoing)
{
    OnGoing.new_inputLenght = 0;
    OnGoing.printing = malloc(1);
    OnGoing.printing[0] = true;
    OnGoing.forkedToKill = true;

    int row = 0;

    for (int i = 0; i < lenght; i++)
    {
        if (strcmp(input[i], "&") == 0) // find out if there are process to start
        {
            if (i == lenght - 1)
            {
                sub_process.numberChilds++;
                sub_process.childs = realloc(sub_process.childs, sub_process.numberChilds);
                sub_process.childs[sub_process.numberChilds - 1] = getpid();
                OnGoing.printing = realloc(OnGoing.printing, sub_process.numberChilds);
                OnGoing.printing[sub_process.numberChilds - 1] = false;
                lenght--;
                break;
            }
            if (i == 0)
            {
                printf("\ncommand not found"); // a process with no argument is not allowed
                return OnGoing;
            }
            row = i;
            break;
        }
    }
    char **background = (char **)malloc(row * sizeof(char *));
    char **new_input = (char **)malloc((lenght - (row + 1)) * sizeof(char *));

    if (row > 0)
    {
        sub_process.numberChilds++;
        sub_process.childs = realloc(sub_process.childs, sub_process.numberChilds);

        OnGoing.printing = realloc(OnGoing.printing, sub_process.numberChilds);
        OnGoing.printing[sub_process.numberChilds] = false;

        for (int i = 0; i < row; i++) // add to background
        {
            background[i] = malloc(strlen(input[i]));
            strcpy(background[i], input[i]);
        }
        for (int i = row + 1; i < lenght; i++) // update the new foreground process
        {
            new_input[i - (row + 1)] = malloc(strlen(input[i]) * sizeof(char *));
            strcpy(new_input[i - (row + 1)], input[i]);
        }

        pid_t child = fork(); // fork process
        if (child == 0)
        {
            OnGoing.new_input = background;
            OnGoing.new_inputLenght = row;

            return OnGoing; // return this OnGoing version to process it in the new branch
        }
        sub_process.childs = realloc(sub_process.childs, sub_process.numberChilds);
        sub_process.childs[sub_process.numberChilds - 1] = child;
        input = new_input;
        lenght = lenght - (row + 1);

        return ampersand(input, lenght, OnGoing); // lets figure out if there are more process to start
    }
    else // if there are no more process, let go on with this state on foreground
    {
        OnGoing.new_input = input;
        OnGoing.new_inputLenght = lenght;
        OnGoing.forkedToKill = false;
    }
    return OnGoing;
}
void kill_zombies(int numberChilds, pid_t *childs)
{
    for (int i = 0; i < numberChilds; i++)
    {
        int status;
        pid_t pid = waitpid(childs[i], &status, WNOHANG);
        if (pid == 0) // not ready to kill
            continue;
        else if (pid == childs[i]) // if there is a pid zombie, let's kill it
        {
            waitpid(childs[i], NULL, 0);
            pid_t *newP = malloc(numberChilds - 1);
            for (int j = 0; j < numberChilds - 1; j++)
            {
                if (childs[j] == childs[i])
                    continue;
                newP[j] = childs[j];
            }
            sub_process.childs = newP;
            sub_process.numberChilds--; // as it's killed, update parent's numberChilds
        }
    }
}
int timeCtrlC = 0;
void Stop(int numberChilds, pid_t *childs)
{
    timeCtrlC++;
    printf("\n%d", timeCtrlC);
    if (timeCtrlC == 2) // call another shell if there are two ctrl+C
    {
        timeCtrlC = 0;
        for (int i = 0; i < numberChilds; i++) // kill all of the parent's child
        {
            kill(childs[i], SIGKILL);
        }
        char *path = NULL;
        int len = 0;
        while (path == NULL) // get current path
        {
            len++;
            path = getcwd(path, len);
        }
        strcat(path, "/output.bin"); // join to the executable to call
        char *arg_Ptr[1];
        arg_Ptr[0] = NULL;
        int err = execv(path, arg_Ptr); // call the shell again
    }
}
void signalFunction()
{
    Stop(sub_process.numberChilds, sub_process.childs);
}
bool IsCommand(char *command)
{
    return true;
}
char *int_tostring(int num)
{
    int i, rem, len = 0, n;
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    char *str = malloc(len);
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
    return str;
}
char *process_id(int num_process, pid_t pid)
{
    char *a = int_tostring((int)pid);
    char *b = int_tostring(num_process);
    char *id = malloc(strlen(a) + strlen(b) + 1);
    int len = strlen(a);
    for (int i = 0; i < len; i++)
    {
        id[i] = a[i];
    }
    id[len] = '_';
    len = strlen(b);
    for (int i = 0; i < len; i++)
    {
        id[i] = b[i];
    }
    return id;
}
