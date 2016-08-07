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
    /**acá inicia el análisis del mkdisk-----------------------------------------------------------------------------*/
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
                    printf("El parámetro %s no pertenece a mkdisk.\n",temporal);
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



/**acá inicia el análisis del rmdisk-----------------------------------------------------------------------------*/
        }else if(strcasecmp(completo, "rmdisk") ==0){
            //reconocer acá los parámetros del rmdisk
            char ruta[100];

            temporal = completo;

            temporal= strtok(NULL, " ::");

            //temporal= strtok(NULL, "::"); printf("After after %s\n",temporal);

            while(temporal != NULL){

                if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    strcpy(ruta,temporal);
                }else{
                    printf("El parámetro %s no pertenece a rmdisk.\n",temporal);
                }

                    temporal = strtok(NULL, "::");
            }
            if(strcmp(ruta,"")!=0){
                printf("Se eliminará un disco:\n");
                char*nombre=strtok(ruta,"\"");
                printf("\t-La ubicación del disco a eliminar es: %s\n",ruta);
                FILE* Fichero;

                    printf("Eliminando disco...\n");
                    if(remove(nombre)==0){
                        printf("Se borró el disco exitosamente :D\n");
                    }else{
                        printf("Debe ingresar una ruta de un disco existente.\n");
                    }
            }


        }else if(strcasecmp(completo, "fdisk") ==0){
/**acá inicia el análisis del fdisk------------------------------------------------------------------------------*/

            int Size=0;         //--------------
            char *unit="";      //--------------
            char *path="";      //--------------
            char *type="";      //--------------
            char *fit="";
            char *Delete="";
            char *name="";      //--------------
            char *add="";
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

                }else if(strcasecmp(temporal, "+type") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    unit = temporal;

                }else if(strcasecmp(temporal, "+fit") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    unit = temporal;

                }else if(strcasecmp(temporal, "+delete") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    unit = temporal;

                }else if(strcasecmp(temporal, "+add") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    unit = temporal;

                }else{
                    printf("El parámetro %s no pertenece a fdisk.\n",temporal);
                }

                    temporal = strtok(NULL, ":: \\");
            }/**Acá debo ver lo del fdisk*/
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
                /**Acá debo ver lo del fdisk*/
            }else{
                printf("No es posible crear el disco, faltan parámetros obligatorios\n");
            }






        }else if(strcasecmp(completo, "mount") ==0){
        /**acá inicia el análisis del mount------------------------------------------------------------------------------*/


        }else if(strcasecmp(completo, "umount") ==0){
        /**acá inicia el análisis del umount-----------------------------------------------------------------------------*/


        }else{
        /**por el momento solo estos comandos, agregar el resto acá------------------------------------------------------*/
            printf("Comando indicado incorrecto.\n");
        }

    }
}



int main(){

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
    printf("\nCreando disco...\n");

    char*nombre=strtok(name,"\"");

    char*ruta=strtok(path,"\"");

    char ValidarRuta[70]="mkdir -p ";

    strcat(ValidarRuta,ruta);

    system(ValidarRuta);

    strcat(ruta,nombre);

    Fichero = fopen (ruta, "w+b");



        while (ContadorCeros<Size/4){
         fwrite("0", 1, sizeof(ContadorCeros),Fichero);
         ContadorCeros++;
        }
        printf("Se creó el disco correctamente :D\n");

   fclose(Fichero);
}

