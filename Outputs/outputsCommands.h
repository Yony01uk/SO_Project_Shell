#include "/media/yonatan01/1602CB9502CB77EF/University/3er/SOperativo/Project_Second_Version/ProcessStarter.h"

#define PERMS 0666
#define FILES_ROOTS "/media/yonatan01/1602CB9502CB77EF/University/3er/SOperativo/Project_Second_Version/Outputs/Outputs_Inputs_Files/"

//EL PARAMETRO *file SIEMPRE DEBE SER LA RUTA COMPLETA DEL ARCHIVO PARA EVITAR CONFUSIONES POSTERIORES

int LeftAngular(char *output,char *file)
{
    FILE *file_dest = fopen(file,"w");
    fputs(output,file_dest);
    fclose(file_dest);
    return 0;
}

int DoubleLeftAngular(char *output,char *file)
{
    FILE *file_dest = fopen(file,"w");
    if(file_dest == NULL)
    {
        creat(file,PERMS);
        file_dest = fopen(file,"w");
    }
    fputs(output,file_dest);
    fclose(file_dest);
    return 0;
}

int RightAngular(char *file)
{
    FILE *file_src = fopen(file,"r");
    if(file_src == NULL)
        return -1;
    fclose(file_src);
    return 0;
}