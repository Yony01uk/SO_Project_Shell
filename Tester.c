#include<sys/wait.h>
#include<unistd.h>
#include<sys/dir.h>
#include "ProcessStarter.h"

#define ROOT_FILES_TEMP "./Outputs/Outputs_Inputs_Files"

void ReadFile(FILE* file)
{
    char *temp = (char *)malloc(sizeof(char)*256);
    while(!feof(file))
    {
        temp = fgets(temp,10000,file);
        printf("%s",temp);
    }
}

void GetCommandResult()
{
    DIR *memory_dir = opendir(ROOT_FILES_TEMP);
    struct dirent *file;
    int a = 2;
    char *result = (char *)malloc(sizeof(char)*256);
    FILE *final_file;
    while((file = readdir(memory_dir)) != NULL)
    {
        if(a > 0)
        {
            a--;
            continue;
        }
        char *location = (char *)malloc(sizeof(char)*256);
        location = strcpy(location,ROOT_FILES_TEMP);
        location = strcat(location,"/");
        location = strcat(location,file->d_name);
        final_file = fopen(location,"r");
        remove(location);
    }
    ReadFile(final_file);
    fclose(final_file);
}

int main()
{
    char *args[] = {"help","nano"};
    char *argv[] = {"0_0","NONE","NONE","help nano"};
    Start(argv[0],argv[1],argv[2]);
    int p;
    int status;
    p = fork();
    if(p == 0)
    {
        execv("./History_Command/historyCommandWorker",argv);
    }
    wait(&status);
    p = fork();
    if(p == 0)
    {
        execv("./MyParser/main",args);
    }
    wait(&status);
    printf("%i\n",status);
    GetCommandResult();
}