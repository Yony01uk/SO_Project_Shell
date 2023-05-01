#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/file.h>

#define COMMAND_OUPUT_ROOT "/media/yonatan01/1602CB9502CB77EF/University/3er/SOperativo/Project_Second_Version/Outputs/Outputs_Inputs_Files/"
#define DIR_OUT "_Dir_Output.txt"
#define DIR_INPUT "_Dir_Input.txt"
#define OUTPUT "_Output.txt"
#define PERMS 0666

char * GetFileName(char *id,char *file_type)
{
    char *result = (char *)malloc(sizeof(char)*256);
    result = strcpy(result,COMMAND_OUPUT_ROOT);
    result = strcat(result,id);
    result = strcat(result,file_type);
    return result;
}

void CreateFiles(int files_count,char *files[])
{
    for(int i = 0; i < files_count; i++)
        creat(files[i],PERMS);
}

int Start(char *id_process,char *dir_input,char *dir_output)
{
    char *files[3];
    for(int i = 0; i < 3; i++)
    {
        files[i] = (char *)malloc(sizeof(char)*256);
        if(i == 0)
            files[i] = GetFileName(id_process,DIR_INPUT);
        else if(i == 1)
            files[i] = GetFileName(id_process,DIR_OUT);
        else
            files[i] = GetFileName(id_process,OUTPUT);
    }
    CreateFiles(3,files);
    FILE *file = fopen(files[0],"w");
    fputs(dir_input,file);
    fclose(file);
    file = fopen(files[1],"w");
    fputs(dir_output,file);
    fclose(file);
}