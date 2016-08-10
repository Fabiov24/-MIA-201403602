#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/**********************VARIABLES**************************************************/
char Entrada[400];
/**********************MÉTODOS****************************************************/
void CrearDisco(int size,char*path,char*name);
/*********************************************************************************/

/**********************STRUCTS****************************************************/
struct Particion{
	char part_status;
	char part_type;
	char part_fit;
    int  part_start;
    int  part_size;
    char part_name[128];
};

struct MBR{
	int mbr_tamano;
	char mbr_fecha_creacion[50];
	int mbr_disk_signature;
	struct Particion mbr_part_1;
	struct Particion mbr_part_2;
	struct Particion mbr_part_3;
	struct Particion mbr_part_4;
	char part_nombre[50];
	int part_inicio;
	int part_tam;
};

struct EBR{
	char part_status;
	char part_fit;
    int part_start;
	int part_size;
	int part_next;
    int part_previous;
	char part_name[25];
};

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

                }else if(strcasecmp(temporal,"\n")==0){
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
                    printf("No es posible crear la partición, el tamaño debe ser mayor a cero.\n");
                }
                if(strcmp(unit,"")!=0){
                    if(strcasecmp(unit,"k")==0){
                        Size = Size * 1024;
                        add = add * 1024;
                    }else if(strcasecmp(unit,"m")==0){
                        Size = Size * 1024*1024;
                        add = add * 1024*1024;
                    }
                }else{
                    unit = "M";
                    Size = Size * 1024*1024;
                    add = add * 1024*1024;
                }
                if(strcmp(path,"")==0){
                    printf("No es posible crear la partición, debe ingresar la ubicación del disco deseado.\n");
                }
                if(strcmp(name,"")==0){
                    printf("No es posible crear la partición, debe ingresar un nombre para la partición.\n");
                }

                if(strcmp(type,"")!=0){
                    if(strcasecmp(type,"p")==0){

                    }else if(strcasecmp(type,"e")==0){

                    }else if(strcasecmp(type,"l")==0){

                    }else{
                        strcpy(type,"ERROR");
                        printf("Error, tipo de partición incorrecto.\n");
                    }
                }else{
                    strcpy(type,"p");
                }

                if(strcmp(fit,"")!=0){
                    if(strcasecmp(fit,"wf")==0){

                    }else if(strcasecmp(fit,"bf")==0){

                    }else if(strcasecmp(fit,"ff")==0){

                    }else{
                        strcpy(fit,"ERROR");
                        printf("Error, ajuste incorrecto.\n");
                    }
                }else{
                    strcpy(fit,"wf");
                }

                if(strcmp(Delete,"")!=0){
                    if(strcasecmp(Delete,"fast")==0){

                    }else if(strcasecmp(Delete,"full")==0){

                    }else{
                        strcpy(Delete,"ERROR");
                        printf("Error, parámetro de eliminacin incorrecto.\n");
                    }
                }

                if(strcmp(add,"")!=0){
                }


            /**Se imprimen los parámetros de la partición*/
                printf("Se creará una nueva partición:\n");


                printf("\t-El tamaño es: %i %sB (%i bytes)\n",SizeAnterior,unit,Size);
                printf("\t-La ubicación del disco es: %s\n",path);
                printf("\t-El nombre de la partición es: %s\n",name);

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


        }else if(strcasecmp(completo,"exec")==0){
// modificar esta info :v

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
                    printf("El parámetro %s no pertenece a exec.\n",temporal);
                }

                    temporal = strtok(NULL, "::");
            }

            char*path=strtok(ruta,"\"");

            FILE *file = fopen (path, "r");
            char Texto[200];
            char Aux[200];
            if(file != NULL){
                while(feof(file)==0){
                    strcpy(Texto,"");
                    fgets(Texto,100,file);
                    strcpy(Aux, Texto);
                    if(Aux[0] != '#'){
                        if((strcasecmp(Texto,"") != 0)){
                            printf("\n\t----Script: %s\n", Texto);
                            AnalizarEntrada(Texto);
                        }

                    }else{
                        printf("\n\t----Comentario: %s\n", Aux);
                    }
                }
                fclose(file);
            }
        }else if(strcasecmp(completo,"\n")==0){
        //esto creo que está de más
        }else if(strcasecmp(completo, "rep") ==0){
        /**acá inicia el análisis del rep------------------------------------------------------------------------------*/

            char *name="";
            char *path="";
            char *id="";
            char *ruta="";
            //reconocer acá los parámetros del rep

            temporal = completo;

            temporal= strtok(NULL, " ::");


            while(temporal != NULL){

                if(strcasecmp(temporal, "-name") ==0){
                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    name=temporal;

                }else if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    path = temporal;

                }else if(strcasecmp(temporal, "-id") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    id = temporal;

                }else if(strcasecmp(temporal, "+ruta") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    ruta = temporal;

                }else if(strcasecmp(temporal,"\n")==0){
                }else{
                    printf("El parámetro %s no pertenece a rep.\n",temporal);
                }

                    temporal = strtok(NULL, ":: \\");
            }



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
        }else if(strcasecmp(Entrada,"\n")==0){
        }else if(strcasecmp(Entrada,"exit")==0){
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

if(Size >= 10485760){
    char*nombre=strtok(name,"\"");

    char*ruta=strtok(path,"\"");

    char ValidarRuta[70]="mkdir -p ";

    strcat(ValidarRuta,ruta);

    system(ValidarRuta);

    strcat(ruta,nombre);

    Fichero = fopen (ruta, "w+b");

        struct MBR mabore;

        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char TiempoActual[128];

        mabore.mbr_tamano = Size;

        strftime(TiempoActual,128,"%d/%m/%y %H:%M:%S\n",tlocal);
        printf("%s", TiempoActual);
        strcpy(mabore.mbr_fecha_creacion,TiempoActual);

        mabore.mbr_disk_signature = (rand() % 26 +1);
        mabore.mbr_part_1.part_status = 'empty';
        mabore.mbr_part_2.part_status = 'empty';
        mabore.mbr_part_3.part_status = 'empty';
        mabore.mbr_part_4.part_status = 'empty';


        while (ContadorCeros<(Size/4)){
         fwrite("0", 1, sizeof(ContadorCeros),Fichero);
         ContadorCeros++;
        }
        rewind(Fichero);
        fwrite(&mabore, sizeof(mabore), 1, Fichero);
        //fwrite(&mabore,1,sizeof(mabore), Fichero);
        fclose(Fichero);
        printf("Se creó el disco correctamente :D\n");

//esto es para leer el archivo
        struct MBR mbr;
        FILE *disco;
        if((fopen (ruta, "rb+")) != NULL){
            disco = fopen (ruta, "rb+");
        }else{
            printf("No existe el archivo indicado :(\n");
        }

        fread (&mbr, sizeof(mbr), 1,disco);
//línea de prueba de lectura del struct D:
        printf("Fecha de creación: %s \n",mbr.mbr_fecha_creacion);

}else{
    printf("* Error: El tamaño mínimo del disco debe ser de 10MB.\n");
}
}

