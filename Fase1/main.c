#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------------
char Entrada[400];
//---------------------------------------------------------------------------------

void AnalizarEntrada(char Texto[]){ //método para analizar los comandos de entrada
    //printf("El texto total es: %s\n",Texto);
    char *completo;
    char *temporal;
    completo = strtok (Texto," \\");
    if (completo != NULL)
    {
        printf ("\nComando: %s\n",completo);

        if(strcasecmp(completo, "mkdisk") ==0){
            //reconocer acá los parámetros del mkdisk
            printf("Vamos a crear un nuevo disco D:\n");

            temporal = completo;

            temporal= strtok(NULL, " ::");

            //temporal= strtok(NULL, "::");

            //printf("After after %s\n",temporal);

            while(temporal != NULL){

                if(strcasecmp(temporal, "-size") ==0){
                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    printf("el tamaño del disco es: %s\n",temporal);
                }else if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    printf("la ubicación del disco es: %s\n",temporal);

                }else if(strcasecmp(temporal, "+unit") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    printf("las unidades son: %s\n",temporal);

                }else{
                    printf("no entro\n");
                }

                    temporal = strtok(NULL, "::");
            }


        }else if(strcasecmp(completo, "rmdisk") ==0){
            //reconocer acá los parámetros del rmdisk
        }
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
            AnalizarEntrada(Entrada);
            //acá debería mandar a analizar el texto
        }
    }while(strcasecmp(Entrada, "exit") !=0);
    return 0;
}
