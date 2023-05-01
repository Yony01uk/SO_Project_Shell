#include "outputsCommands.h"

int main(int argc, char *argv[])
{
    if(strcmp(argv[0],"l_a") == 0)
        return LeftAngular(argv[1],argv[2]);
    if(strcmp(argv[0],"d_l_a") == 0)
        return DoubleLeftAngular(argv[1],argv[2]);
    if(strcmp(argv[0],"r_a") == 0)
        return RightAngular(argv[1]);
}