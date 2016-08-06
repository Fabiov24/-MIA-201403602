#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*********************************************************************************/
char Entrada[400];
/*********************************************************************************/
void CrearDisco(int size,char*path,char*name);
/*********************************************************************************/

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

                }else if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    path = temporal;

                }else if(strcasecmp(temporal, "+unit") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    unit = temporal;

                }else if(strcasecmp(temporal, "-name") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    name = temporal;

                }else{
                    printf("Parámetro incorrecto: %s\n",temporal);
                }

                    temporal = strtok(NULL, ":: \\");
            }
            if(Size != 0 && strcmp(path,"")!=0 && strcmp(name,"")!=0 ){
                int SizeAnterior=Size;
                if(Size<=0){
                    printf("No es posible crear el disco, el tamaño debe ser mayor a cero.\n");
                }
                if(strcmp(unit,"")!=0){
                    if(strcasecmp(unit,"k")==0){
                        Size = Size * 1024;
                    }else if(strcasecmp(unit,"m")==0){
                        Size = Size * 1024*1024;
                    }
                }else{
                    unit = "M";
                    Size = Size * 1024*1024;
                }
                if(strcmp(path,"")==0){
                    printf("No es posible crear el disco, debe ingresar una ubicación para crear el disco.\n");
                }
                if(strcmp(name,"")==0){
                    printf("No es posible crear el disco, debe ingresar un nombre para el disco.\n");
                }
            /**Se imprimen los parámetros del disco*/
                printf("Se creará un nuevo disco:\n");
                printf("\t-El tamaño del disco es: %i %sB (%i bytes)\n",SizeAnterior,unit,Size);
                printf("\t-La ubicación del disco es: %s\n",path);
                printf("\t-El nombre del disco es: %s\n",name);

            /**Se envían los parámetros al método para crear el disco*/
                CrearDisco(Size,path,name);

            }else{
                printf("No es posible crear el disco, faltan parámetros obligatorios\n");
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
        }else if(strcasecmp(Entrada,"clear")==0){
            system("clear");
        }else{
            AnalizarEntrada(Entrada);
            //acá debería mandar a analizar el texto
        }
    }while(strcasecmp(Entrada, "exit") !=0);
    return 0;
}

void CrearDisco(int Size,char*path,char*name){
    FILE  *Fichero;
    int ContadorCeros=0;
    printf("Creando disco...\n");

    char*nombre=strtok(name,"\"");
    Fichero = fopen (nombre, "w+b");
//    fwrite (buffer, 1, leidos, Fichero);
    if (Fichero==NULL){
        perror("No se puede el fichero");
    }
    while (ContadorCeros<Size/4){
         fwrite("0", 1, sizeof(ContadorCeros),Fichero);
         ContadorCeros++;
    }

   fclose(Fichero);
}
