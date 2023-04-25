#include "helpCommand.h"
#include<syslog.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    char *result = helpCommandWorker(argv[1]);
    printf("%s\n",result);

    return 0;
}