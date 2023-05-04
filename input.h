#include <stdio.h>
char *InputX()
{
    char *input = NULL;
    size_t len = 0;
    int n = getline(&input, &len, stdin);

    return input;
}
