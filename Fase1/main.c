#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------------
char Entrada[400];
//---------------------------------------------------------------------------------

void AnalizarEntrada(char Texto[]){ //método para analizar los comandos de entrada
    printf("%s\n",Texto);
    char *completo;

    completo = strtok (Texto," \\");
    while (completo != NULL)
    {
        printf ("%s\n",completo);

        if(strcasecmp(completo, "mkdisk") !=0){
            //reconocer acá los parámetros del mkdisk


        }else if(strcasecmp(completo, "rmdisk") !=0){
            //reconocer acá los parámetros del rmdisk
        }


        completo = strtok (NULL, " \\");
    }
}



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
            printf("Se leyó el segundo %s %s \n",EntradaAnterior,Entrada);//línea de prueba :v
            strcat(EntradaAnterior," ");
            strcat(EntradaAnterior,Entrada);

            AnalizarEntrada(EntradaAnterior);
        }else{
            //acá debería mandar a analizar el texto
        }
    }while(strcasecmp(Entrada, "exit") !=0);
    return 0;
}
