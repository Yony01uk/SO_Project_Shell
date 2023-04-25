#include "againCommand.h"

int main(int argc, char *argv[])
{
    char *command = (char *)malloc(sizeof(char)*256);
    int id = atoi(argv[1]);
    command = SearchCommand(id);
    printf("%s\n",command);
}