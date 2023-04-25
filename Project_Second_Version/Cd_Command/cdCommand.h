#include<stdlib.h>
#include<unistd.h>
#include<sys/dir.h>

//este codigo debe ir en el main del shell para que todo el proceso cambie el entorno donde se desarrolla
char *GetCurrentDirectory()
{
    char *current_directory;
    int buf_size = 0;
    while((current_directory = getcwd(current_directory,buf_size)) == NULL)
        buf_size++;
    return current_directory;
}

char *cdCommand(char *dir)
{
    DIR *dir_to_open;
    if((dir_to_open = opendir(dir)) == NULL)
        return "";
    chdir(dir);
    return dir;
}