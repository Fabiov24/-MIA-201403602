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

        while(Entrada[0] == '#'){
            scanf(" %[^\n]s", Entrada);
        }

        if(Entrada[strlen(Entrada)-1] == '\\'){
            char EntradaAnterior[strlen(Entrada)] ;
            strcpy(EntradaAnterior,Entrada);
            scanf(" %[^\n]s", Entrada);
            printf("Se leyó el segundo %s %s \n",EntradaAnterior,Entrada);
        }else{

        }
    }while(strcasecmp(Entrada, "exit") !=0);
    return 0;
}
