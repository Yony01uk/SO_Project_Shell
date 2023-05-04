#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "command.h"
#include <stdio.h>
bool IF_Finder(char *string, Parser_Variables parser) // let's find wheter there are condions or not
{
    //////////// times a if,then,end is found///////////////
    int if_found = 0;
    int then_found = 0;
    int end_found = 0;
    ///////////////////////////////////////////////////////
    int *walking = (int *)malloc(0); // pointer to walk throught another int array pointer
    walking = (int *)realloc(walking, parser.StringLenght);
    char *auxiliar = (char *)malloc(0); // pointer to walk throught another char array pointer
    auxiliar = (char *)realloc(auxiliar, parser.StringLenght);

    for (int i = 0; i < parser.StringLenght; i++)
    {
        if (i + 1 < parser.StringLenght && ((*(string + i) == 'i' && *(string + i + 1) == 'f')))
        {
            // If
            if (if_found - then_found != 0)
            {
                printf("\n%d", i);
                printf("\nunexpected if");
                return false;
            }

            if_found++;
            // I need to add to IF_ElseArray if a "if" is found, and where is found at indexes
            *(auxiliar++) = 'I';
            *(walking++) = i;
            ///////////////////////////////////////////////////
            i++;
            continue;
        }
        if (i + 3 < parser.StringLenght && ((*(string + i) == 't' && *(string + i + 1) == 'h' && *(string + i + 2) == 'e' && *(string + i + 3) == 'n')))
        {
            // then
            if (if_found - then_found != 1)
            {
                printf("\nunexpected then");
                return false;
            }
            then_found++;
            // I need to add to IF_ElseArray if a "then" is found, and where is found at indexes
            *(walking++) = i;
            *(auxiliar++) = 't';
            ///////////////////////////////////////////////////
            i += 3;
            continue;
        }
        if (i + 3 < parser.StringLenght && ((*(string + i) == 'e' && *(string + i + 1) == 'l' && *(string + i + 2) == 's' && *(string + i + 3) == 'e')))
        {
            // else
            if (if_found == 0 || if_found - then_found != 0 || then_found - end_found == 0)
            {
                printf("\nunexpected else");
                return false;
            }
            // I need to add to IF_ElseArray if a "else" is found, and where is found at indexes
            *(auxiliar++) = 'e';
            *(walking++) = i;
            ///////////////////////////////////////////////////
            i += 3;
            continue;
        }
        if (i + 2 < parser.StringLenght && ((*(string + i) == 'e' && *(string + i + 1) == 'n' && *(string + i + 2) == 'd')))
        {
            // end
            if (if_found == 0 || if_found - then_found != 0 || *(auxiliar - 1) == 'I')
            {
                printf("\nunexpected end");
                return false;
            }

            end_found++;
            // I need to add to IF_ElseArray if a "end" is found, and where is found at indexes
            *(walking++) = i;
            *(auxiliar++) = 'E';
            ///////////////////////////////////////////////////
            i += 2;
            if (then_found - end_found == 0) // if this end is a conditional terminator, we need to let konw
            {
                *(auxiliar - 1) = 'F';
                *(walking - 1) += 2; // we'll give to the "terminatior end" the index of the confictional termination
            }
            continue;
        }
    }
    if (if_found != 0 && !(then_found != 0 && then_found - end_found == 0)) // if there are if but do not close its scope,it's fake
        return false;

    return true;
}
Parser_Variables FunctionRecognizer(char *input, int StringLenght) // divedes input in strings
{
    Parser_Variables parser;
    int *p[StringLenght];
    int lenght = 0;
    char *NewInput[StringLenght];

    for (int i = 0; i < StringLenght; i++)
    {
        if (input[i] == ' ')
            continue;
        int lenght1 = 0;
        NewInput[lenght] = (char *)malloc(lenght1);
        for (int j = i; j < StringLenght; j++)
        {
            if (input[j] == ' ') // if space break otherwise add to new input
            {
                i = j;
                break;
            }
            NewInput[lenght] = (char *)realloc(NewInput[lenght], lenght1 + 1);
            NewInput[lenght][lenght1] = input[j];
            i = j;
            lenght1++;
        }
        p[lenght] = (int *)malloc(sizeof(int *));
        p[lenght][0] = lenght1;
        lenght++;
    }
    char **NewInput1 = (char **)malloc(lenght * sizeof(char *));

    for (int i = 0; i < lenght; i++) // put into a char**
    {
        NewInput1[i] = (char *)malloc(p[i][0]);
        for (int j = 0; j < p[i][0]; j++)
            NewInput1[i][j] = NewInput[i][j];
    }
    parser.NewContractedForm = NewInput1;
    parser.NewContractedForm_Lenght = lenght;
    return parser;
}
Parser_Variables ToParse(char *input, Parser_Variables parser)
{
    if (!IF_Finder(input, parser))
        return parser;
    Parser_Variables aux = FunctionRecognizer(input, parser.StringLenght);
    parser.NewContractedForm = aux.NewContractedForm;
    parser.NewContractedForm_Lenght = aux.NewContractedForm_Lenght;
    return parser;
}