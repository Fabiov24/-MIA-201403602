#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Sección para variables
*/
char Entrada[400];

int main()
{
    system("clear");

    printf("------------------ Bienvenido al sistema  ------------------ \n");

    do{
    printf("Ingresar un comando \n");
    scanf(" %[^\n]s", Entrada);
    }while(strcmp(Entrada, "exit") !=0);



    return 0;
}
