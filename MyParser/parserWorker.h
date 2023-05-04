#include "../ProcessStarter.h"

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

void readCommandSection(int init,int end,char *argv[],char *dest[])
{
    for(int i = init; i < end; i++)
        dest[i - init] = strcpy(dest[i -init],argv[i]);
}

int MovePointer(int init,int argc,char *argv[])
{
    for(int i = init; i < argc; i++)
    {
        if(strcmp(argv[i],";") == 0 || strcmp(argv[i],"||") == 0 || strcmp(argv[i],"&&") == 0)
            return i;
    }
    return argc;
}

int RedirectionIndex( int end,char *command_line[])
{
    for(int i = 0; i < end; i++)
        if(strcmp(command_line[i],">") == 0 || strcmp(command_line[i],">>") == 0 || strcmp(command_line[i],"<") == 0 || strcmp(command_line[i],"|") == 0)
            return i;
    return end;
}

