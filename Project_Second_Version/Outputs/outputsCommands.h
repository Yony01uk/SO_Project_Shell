#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/file.h>

#define PERMS 0666
#define FILES_ROOTS "/media/yonatan01/1602CB9502CB77EF/University/3er/SOperativo/Project_Second_Version/Outputs/Outputs_Inputs_Files/"

//EL PARAMETRO *file SIEMPRE DEBE SER LA RUTA COMPLETA DEL ARCHIVO PARA EVITAR CONFUSIONES POSTERIORES

int LeftAngular(char *command,char *file)
{
    //construimos la ruta al archivo correspondiente al comando
    char *file_name = (char *)malloc(sizeof(char)*256);
    file_name = strcpy(file_name,FILES_ROOTS);
    file_name = strcat(file_name,command);
    file_name = strcat(file_name,"_Output.txt");
    FILE *file_dest;
    file_dest = fopen(file_name,"w");
    fputs("stdout",file_dest);
    fclose(file_dest);
    FILE *file_out;
    if((file_out = fopen(file,"r")) == NULL)
        return -1;
    file_dest = fopen(file_name,"w");
    fclose(file_out);
    fputs(file,file_dest);
    fclose(file_dest);
    return 0;
}

int DoubleLeftAngular(char *command,char *file)
{
    //construimos la ruta del archivo correspondiente al comando
    char *file_name = (char *)malloc(sizeof(char)*256);
    file_name = strcpy(file_name,FILES_ROOTS);
    file_name = strcat(file_name,command);
    file_name = strcat(file_name,"_Output.txt");
    FILE *file_dest;
    file_dest = fopen(file_name,"w");
    FILE *file_out;
    if((file_out = fopen(file,"r")) == NULL)
    {
        creat(file,PERMS);
        file_out = fopen(file,"r");
    }
    fclose(file_out);
    fputs(file,file_dest);
    fclose(file_dest);
    return 0;
}

int RightAngular(char *command,char *file)
{
    //construimos la ruta del archivo correspondiente al comando
    char *file_name = (char *)malloc(sizeof(char)*256);
    file_name = strcpy(file_name,FILES_ROOTS);
    file_name = strcat(file_name,command);
    file_name = strcat(file_name,"_Input.txt");
    FILE *file_dest;
    file_dest = fopen(file_name,"w");
    fputs("stdin",file_dest);
    fclose(file_dest);
    FILE *file_in;
    if((file_in = fopen(file,"r")) == NULL)
        return -1;
    file_dest = fopen(file_name,"w");
    fclose(file_in);
    fputs(file,file_dest);
    fclose(file_dest);
    return 0;
}