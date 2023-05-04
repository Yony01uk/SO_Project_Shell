#include "../ProcessStarter.h"

int main(int argc,char *argv[])
{
    char *file_location_in = (char *)malloc(sizeof(char)*256);
    char *file_location_out = (char *)malloc(sizeof(char)*256);
    char *file_out = (char *)malloc(sizeof(char)*256);
    char *result = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    file_location_in = GetFileName(argv[0],DIR_INPUT);
    file_location_out = GetFileName(argv[0],DIR_OUT);
    file_out = GetFileName(argv[0],OUTPUT);
    FILE *file;
    file = fopen(file_location_in,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        chdir(argv[3]);
    }
    else
    {
        fclose(file);
        file = fopen(data,"r");
        data = fgets(data,10000,file);
        result = chdir(data);
        fclose(file);
    }
    file = fopen(file_location_out,"r");
    data = fgets(data,10000,file);
    if(strcmp(data,"NONE") == 0)
    {
        fclose(file);
        file = fopen(file_out,"w");
        fputs(argv[3],file);
        fclose(file);
    }
    else
    {
        fclose(file);
        file = fopen(data,"w");
        fputs(argv[3],file);
        fclose(file);
    }
}