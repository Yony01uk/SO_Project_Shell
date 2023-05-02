#include "../ProcessStarter.h"

#define PERMS 0666
#define FILES_ROOTS "./Outputs/Outputs_Inputs_Files/"

//EL PARAMETRO *file SIEMPRE DEBE SER LA RUTA COMPLETA DEL ARCHIVO PARA EVITAR CONFUSIONES POSTERIORES

int LeftAngular(char *command_id,char *file)
{
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(command_id,DIR_OUT);
    FILE *f_out = fopen(file,"r");
    if(f_out == NULL)
        return -1;
    fclose(f_out);
    f_out = fopen(file_location,"w");
    fputs(file,f_out);
    fclose(f_out);
    return 0;
}

int DoubleLeftAngular(char *command_id,char *file)
{
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(command_id,DIR_OUT);
    FILE *f_out = fopen(file,"r");
    if(f_out == NULL)
        creat(file,PERMS);
    f_out = fopen(file_location,"w");
    fputs(file,f_out);
    fclose(f_out);
    return 0;
}

int RightAngular(char *command_id,char *file)
{
    char *file_location = (char *)malloc(sizeof(char)*256);
    file_location = GetFileName(command_id,DIR_INPUT);
    FILE *f_out = fopen(file,"r");
    if(f_out == NULL)
        return -1;
    fclose(f_out);
    f_out = fopen(file_location,"w");
    fputs(file,f_out);
    fclose(f_out);
    return 0;
}

int Pipe(char *command_id_1,char *command_id_2)
{
    char *file_location1 = (char *)malloc(sizeof(char)*256);
    char *file_location2 = (char *)malloc(sizeof(char)*256);
    char *data = (char *)malloc(sizeof(char)*256);
    file_location1 = GetFileName(command_id_1,DIR_OUT);
    file_location2 = GetFileName(command_id_2,DIR_INPUT);
    FILE *file = fopen(file_location1,"r");
    data = fgets(data,sizeof(data),file);
    fclose(file);
    if(strcmp(data,"NONE") == 0)
        file_location1 = GetFileName(command_id_1,OUTPUT);
    file = fopen(file_location2,"w");
    fputs(file_location1,file);
    fclose(file);
    return 0;
}