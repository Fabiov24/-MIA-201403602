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
        if(strcasecmp(completo, "mkdisk") ==0){
            int Size=0;
            char *unit="";
            char *path="";
            char *name="";
            //reconocer acá los parámetros del mkdisk
            printf("Vamos a crear un nuevo disco D:\n");

            temporal = completo;

            temporal= strtok(NULL, " ::");

            //temporal= strtok(NULL, "::");//printf("After after %s\n",temporal);

            while(temporal != NULL){

                if(strcasecmp(temporal, "-size") ==0){
                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    Size = atoi(temporal);

                    printf("El tamaño del disco es: %s\n",temporal);
                }else if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    printf("La ubicación del disco es: %s\n",temporal);

                }else if(strcasecmp(temporal, "+unit") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    printf("Las unidades son: %s\n",temporal);

                }else if(strcasecmp(temporal, "-name") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    printf("El nombre del disco es: %s\n",temporal);

                }else{
                    printf("Parámetro incorrecto: %s\n",temporal);
                }

                    temporal = strtok(NULL, ":: \\");
            }

            if(Size<=0){
                printf("No es posible crear el disco, el tamaño debe ser mayor a cero.\n");
            }
            if(strcmp(unit,"")!=0){
                if(strcasecmp(unit,"k")==0){
                Size = Size * 1024;
                }
                if(strcasecmp(unit,"m")==0){
                Size = Size * 1024*1024;
                }
            }
            if(strcmp(path,"")==0){
                printf("No es posible crear el disco, debe ingresar una ubicación para crear el disco.\n");
            }
            if(strcmp(name,"")==0){
                printf("No es posible crear el disco, debe ingrear un nombre para el disco.\n");
            }

//fin mkdisk
        }else if(strcasecmp(completo, "rmdisk") ==0){
            //reconocer acá los parámetros del rmdisk

            printf("Vamos a eliminar el disco D:\n");

            temporal = completo;

            temporal= strtok(NULL, " ::");

            //temporal= strtok(NULL, "::");

            //printf("After after %s\n",temporal);

            while(temporal != NULL){

                if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    printf("la ubicación del disco es: %s\n",temporal);

                }else{
                    printf("Parámetro incorrecto\n");
                }

                    temporal = strtok(NULL, "::");
            }

//fin rmdisk
        }else{
            printf("Comando indicado incorrecto.\n");
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
