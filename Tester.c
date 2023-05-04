#include<sys/wait.h>
#include<unistd.h>
#include "ProcessStarter.h"

int main()
{
    char *args[] = {"get","|","help","|","set"};
    char *argv[] = {"0_0","NONE","NONE","get | help | set"};
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
}