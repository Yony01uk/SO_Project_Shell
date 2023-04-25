#include<stdio.h>
#include<string.h>

#define HISTORY_FILE "History.txt"
#define HISTORY_SIZE 10

int historyCommandWorker(char *command)
{
    int command_number = 0;
    char *history[HISTORY_SIZE];
    //abrimos el archivo para revisar
    FILE *file = fopen(HISTORY_FILE,"r");
    int c = fgetc(file);
    int close;
    //averiguamos si ya existe algo en el historial
    if (c != EOF)
        c = 1;
    else
        c = 0;
    //cerramos para volver a abrirlo desde el principio
    fclose(file);
    file = fopen(HISTORY_FILE,"r");
    while(!feof(file) && c == 1)
    {
        if(command_number == 10)
            break;
        //leemos el archivo
        history[command_number] = (char *)malloc(sizeof(char)*256);
        history[command_number] = fgets(history[command_number],100000,file);
        //escribimos el historial
        printf("%s",history[command_number]);
        //contamos cuantos comandos hay
        command_number++;
    }
    //cerramos el archivo para luego abrirlo para escritura
    fclose(file);
    if(command_number == 10)
        command_number--;
    //actualizamos el historial, el primero es el comando mas reciente
    for(int i = command_number; i > 0; i--)
    {
        history[i] = (char *)malloc(sizeof(char)*256);
        history[i] = strcpy(history[i],history[i - 1]);
    }
    if(command_number == 0)
        history[0] = (char *)malloc(sizeof(char)*256);
    history[0] = strcpy(history[0],command);
    //escribimos el historial
    file = fopen(HISTORY_FILE,"w");
    for(int i = 0; i < command_number + 1; i++)
    {
        if(i == 0)
        {
            if(command_number > 0)
                fprintf(file,"%s\n",history[i]);
            else
                fprintf(file,"%s",history[i]);
        }
        else
            fprintf(file,"%s",history[i]);
    }    
    fclose(file);
    return 0;
}