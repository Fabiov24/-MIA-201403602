#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/**********************VARIABLES**************************************************/
char Entrada[400];
/**********************MÉTODOS****************************************************/
void CrearDisco(int size,char*path,char*name);
void CrearParticion(int size,char path[],char name[],char unit[],char type[],char fit[],char Delete[],int add);

/*********************************************************************************/

/**********************STRUCTS****************************************************/
struct Particion{
	char part_status[10];
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
	char part_status[10];
	char part_fit;
    int part_start;
	int part_size;
	int part_next;
    int part_previous;
	char part_name[25];
};

/*********************************************************************************/

/** Por no tener los structs arriba, esta declaración queda acá :(*/
void ReporteMBR(struct MBR mabore);
void ReporteDisk(struct MBR mabore);



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
            char *aux="";
            //reconocer acá los parámetros del mkdisk

            temporal = completo;

            temporal= strtok(NULL, "::");

            //temporal= strtok(NULL, "::");//printf("After after %s\n",temporal);

            while(temporal != NULL){

                if(strcasecmp(temporal, "-size") ==0){
                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    Size = atoi(temporal);

                }else if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, ":\"");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }


                path=temporal;

                    //          path = temporal;


                    //aux = strtok (NULL,"\"");

                    /*if (aux[0] == ':'){
                        memmove(aux, aux+1, strlen(aux));
                    }*/
                    //path = aux;

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

                    temporal= strtok(NULL, ":\"");

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

            int Size=0;
            char unit[2];
            char path[100];
            char type[2];
            char fit[2];
            char Delete[50];
            char name[100];
            int add=0;

            strcpy(unit,"");
            strcpy(path,"");
            strcpy(type,"");
            strcpy(fit,"");
            strcpy(Delete,"");
            strcpy(name,"");

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
                    //add = Size;

                }else if(strcasecmp(temporal, "-path") ==0){

                    temporal= strtok(NULL, ":\"");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    //path = temporal;
                    strcpy(path,temporal);

                }else if(strcasecmp(temporal, "+unit") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    //unit = temporal;
                    strcpy(unit,temporal);

                }else if(strcasecmp(temporal, "-name") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    //name = temporal;
                    strcpy(name,temporal);

                }else if(strcasecmp(temporal, "+type") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    //type = temporal;
                    strcpy(type,temporal);

                }else if(strcasecmp(temporal, "+fit") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    //fit = temporal;
                    strcpy(fit,temporal);

                }else if(strcasecmp(temporal, "+delete") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }

                    //Delete = temporal;
                    strcpy(Delete,temporal);

                }else if(strcasecmp(temporal, "+add") ==0){

                    temporal= strtok(NULL, " ");

                    if (temporal[0] == ':'){
                        memmove(temporal, temporal+1, strlen(temporal));
                    }
                    add = atoi(temporal);


                }else{
                    printf("El parámetro %s no pertenece a fdisk.\n",temporal);
                }

                    temporal = strtok(NULL, ":: \\");
            }
            /**Acá debo ver lo del fdisk*/

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
                    else if(strcasecmp(unit,"b")==0){
                    }
                }else{
                    strcpy(unit,"K");
                    Size = Size * 1024;
                    add = add * 1024;
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

                if(strcmp(Delete,"")!=0){
                }

            /**Se imprimen los parámetros de la partición*/
                printf("Se creará una nueva partición:\n");


                printf("\t-El tamaño es: %i %sB (%i bytes)\n",SizeAnterior,unit,Size);
                printf("\t-La ubicación del disco es: %s\n",path);
                printf("\t-El nombre de la partición es: %s\n",name);

            /**Se envían los parámetros al método para crear partición */
                CrearParticion(Size,path,name,unit,type,fit,Delete,add);
            }else{
                printf("No es posible crear la partición, faltan parámetros obligatorios\n");
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

                    temporal= strtok(NULL, ":\"");

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

                    temporal= strtok(NULL, ":\"");

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

    char*ruta;
    if(path[0]=="\""){
    ruta=strtok(path,"\"");
    }else{
    ruta = path;
    }



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
        strcpy(mabore.mbr_part_1.part_status ,"empty");
        strcpy(mabore.mbr_part_2.part_status ,"empty");
        strcpy(mabore.mbr_part_3.part_status ,"empty");
        strcpy(mabore.mbr_part_4.part_status ,"empty");


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


void CrearParticion(int Size,char path[],char name[],char unit[],char type[],char fit[],char Delete[],int add){

char*ruta=strtok(path,"\"");
char*nombre=strtok(name,"\"");
FILE * DiscoActual = fopen(ruta, "r+b");

printf("Creando partición...\n");

if(DiscoActual != NULL){ //Validar que el archivo exista
    if(strcasecmp(unit,"") == 0 || strcasecmp(unit,"b") == 0 || strcasecmp(unit,"k") == 0 || strcasecmp(unit,"m") == 0){
        if(strcmp(fit,"") == 0 || strcmp(fit,"bf") == 0 || strcmp(fit,"ff") == 0 || strcmp(fit,"wf") == 0){

        struct MBR mbr;
        fread (&mbr, sizeof(mbr), 1,DiscoActual);


        if((strcmp(Delete,"") == 0) && (add == 0)) { //cuando cumple esto es porque va a crear una partición  :v
            if(Size>=2048){

                if(strcmp(type,"") == 0 || strcmp(type,"p") == 0 ){

                    if((strcmp(mbr.mbr_part_1.part_status,"empty")==0) || (strcmp(mbr.mbr_part_2.part_status,"empty")==0) || (strcmp(mbr.mbr_part_3.part_status,"empty")==0 )|| (strcmp(mbr.mbr_part_4.part_status,"empty")==0 )){

                        if(strcasecmp(mbr.mbr_part_1.part_status,"empty")==0){
                            /** Encontró espacio disponible en la partición 1 */
                            int Inicio_Espacio_Disponible= sizeof(mbr);
                            int Final_Espacio_Disponible = mbr.mbr_tamano;

                            if((Final_Espacio_Disponible - Inicio_Espacio_Disponible) >= Size){

                                    strcpy(mbr.mbr_part_1.part_name, nombre);
                                    mbr.mbr_part_1.part_start = Inicio_Espacio_Disponible;
                                    strcpy(mbr.mbr_part_1.part_status,"Busy");
                                    mbr.mbr_part_1.part_size = Size;
                                    mbr.mbr_part_1.part_type = 'P';
                                    mbr.mbr_part_1.part_fit = fit[0];

                                    printf("Se creó la partición primaria %s exitosamente, en la posición 1.\n", name);

                            }else{
                                  printf("No fue posible crear la partición, no queda espacio disponible.\n");
                            }
                        }
                        else if(strcasecmp(mbr.mbr_part_2.part_status,"empty")==0){

                        /** Encontró espacio disponible en la partición 2 */

                            int Inicio_Espacio_Disponible= mbr.mbr_part_1.part_start + mbr.mbr_part_1.part_size;
                            int Final_Espacio_Disponible = mbr.mbr_tamano ;

                            if((Final_Espacio_Disponible - Inicio_Espacio_Disponible) >= Size){

                                    strcpy(mbr.mbr_part_2.part_name, nombre);
                                    mbr.mbr_part_2.part_start = Inicio_Espacio_Disponible;
                                    strcpy(mbr.mbr_part_2.part_status,"Busy");
                                    mbr.mbr_part_2.part_size = Size;
                                    mbr.mbr_part_2.part_type = 'P';
                                    mbr.mbr_part_2.part_fit = fit[0];

                                    printf("Se creó la partición primaria %s exitosamente, en la posición 2.\n", name);

                            }else{
                                  printf("No fue posible crear la partición, no queda espacio disponible.\n");
                            }

                        }
                        else if(strcasecmp(mbr.mbr_part_3.part_status,"empty")==0){

                            /** Encontró espacio disponible en la partición 3 */

                            int Inicio_Espacio_Disponible= mbr.mbr_part_2.part_start + mbr.mbr_part_2.part_size;
                            int Final_Espacio_Disponible = mbr.mbr_tamano ;

                            if((Final_Espacio_Disponible - Inicio_Espacio_Disponible) >= Size){

                                    strcpy(mbr.mbr_part_3.part_name, nombre);
                                    mbr.mbr_part_3.part_start = Inicio_Espacio_Disponible;
                                    strcpy(mbr.mbr_part_3.part_status,"Busy");
                                    mbr.mbr_part_3.part_size = Size;
                                    mbr.mbr_part_3.part_type = 'P';
                                    mbr.mbr_part_3.part_fit = fit[0];

                                    printf("Se creó la partición primaria %s exitosamente, en la posición 3.\n", name);

                            }else{
                                  printf("No fue posible crear la partición, no queda espacio disponible.\n");
                            }


                        }
                        else if(strcasecmp(mbr.mbr_part_4.part_status,"empty")==0){

                       /** Encontró espacio disponible en la partición 4 */

                            int Inicio_Espacio_Disponible= mbr.mbr_part_3.part_start + mbr.mbr_part_3.part_size;
                            int Final_Espacio_Disponible = mbr.mbr_tamano ;

                            if((Final_Espacio_Disponible - Inicio_Espacio_Disponible) >= Size){

                                    strcpy(mbr.mbr_part_4.part_name, nombre);
                                    mbr.mbr_part_4.part_start = Inicio_Espacio_Disponible;
                                    strcpy(mbr.mbr_part_4.part_status,"Busy");
                                    mbr.mbr_part_4.part_size = Size;
                                    mbr.mbr_part_4.part_type = 'P';
                                    mbr.mbr_part_4.part_fit = fit[0];

                                    printf("Se creó la partición primaria %s exitosamente, en la posición 4.\n", name);

                            }else{
                                  printf("No fue posible crear la partición, no queda espacio disponible.\n");
                            }

                        }else{
                            printf("\n");
                        }



                    }else{
                        printf("Se encuentran ocupadas las 4 particiones, no es posible crear más.\n");
                    }

                }else if(strcmp(type,"e") == 0){

                }


            }else{
                printf("Error, el tamaño mínimo de una partición debe ser de 2MB.\n");
            }

        }else{
            printf("Esto no lo he validado todavía D: %i\n",add);
        }
        rewind(DiscoActual);
        fwrite(&mbr,sizeof(mbr),1,DiscoActual);
        fclose(DiscoActual);
        ReporteMBR(mbr);


        }else{
            printf("El tipo de ajuste debe ser BF, FF ó WF.\n");
        }
    }else{
        printf("Las unidades deben estar en B, KB o MB.\n");
    }

}else{
    printf("No existe el disco en el path indicado.\n");
}
}

void ReporteMBR(struct MBR mabore){
    FILE *fp;
 	fp = fopen ( "MBR.dot", "w+" );
    fprintf(fp," digraph {\n");


    fprintf(fp,"label=<<B>Master Boot Record </B>>;\n");
    fprintf(fp,"fontsize=17;");
    fprintf(fp,"node [shape=plaintext fontname = \"Ubuntu\"];\n");
    fprintf(fp,"node [shape=plaintext fontname = \"Ubuntu\"];\n");
    fprintf(fp,"graph [fontname = \"Ubuntu\"];\n");

    fprintf(fp,"MBR [label=<<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n");
    fprintf(fp,"<tr><td bgcolor=\"#DB351B\"><b>Nombre</b></td><td bgcolor=\"#DB351B\"><b>Valor</b></td></tr> \n");

    fprintf(fp,"<tr><td><b>mbr_tamaño</b></td><td>%i</td></tr>\n",mabore.mbr_tamano);
    fprintf(fp,"<tr><td><b>mbr_fecha_creacion</b></td><td>%s</td></tr>\n",mabore.mbr_fecha_creacion);
    fprintf(fp,"<tr><td><b>mbr_disk_signature</b></td><td>%i</td></tr>\n",mabore.mbr_disk_signature);

    fprintf(fp,"<tr><td><b>part_status_1</b></td><td>%s</td></tr>\n",mabore.mbr_part_1.part_status);
    fprintf(fp,"<tr><td><b>part_type_1</b></td><td>%c</td></tr>\n",mabore.mbr_part_1.part_type);
    fprintf(fp,"<tr><td><b>part_fit_1</b></td><td>%c</td></tr>\n",mabore.mbr_part_1.part_fit);
    fprintf(fp,"<tr><td><b>part_start_1</b></td><td>%i</td></tr>\n",mabore.mbr_part_1.part_start);
    fprintf(fp,"<tr><td><b>part_size_1</b></td><td>%i</td></tr>\n",mabore.mbr_part_1.part_size);
    fprintf(fp,"<tr><td><b>part_name_1</b></td><td>%s</td></tr>\n",mabore.mbr_part_1.part_name);

	fprintf(fp,"<tr><td><b>part_status_2</b></td><td>%s</td></tr>\n",mabore.mbr_part_2.part_status);
    fprintf(fp,"<tr><td><b>part_type_2</b></td><td>%c</td></tr>\n",mabore.mbr_part_2.part_type);
    fprintf(fp,"<tr><td><b>part_fit_2</b></td><td>%c</td></tr>\n",mabore.mbr_part_2.part_fit);
    fprintf(fp,"<tr><td><b>part_start_2</b></td><td>%i</td></tr>\n",mabore.mbr_part_2.part_start);
    fprintf(fp,"<tr><td><b>part_size_2</b></td><td>%i</td></tr>\n",mabore.mbr_part_2.part_size);
    fprintf(fp,"<tr><td><b>part_name_2</b></td><td>%s</td></tr>\n",mabore.mbr_part_2.part_name);

	fprintf(fp,"<tr><td><b>part_status_3</b></td><td>%s</td></tr>\n",mabore.mbr_part_3.part_status);
    fprintf(fp,"<tr><td><b>part_type_3</b></td><td>%c</td></tr>\n",mabore.mbr_part_3.part_type);
    fprintf(fp,"<tr><td><b>part_fit_3</b></td><td>%c</td></tr>\n",mabore.mbr_part_3.part_fit);
    fprintf(fp,"<tr><td><b>part_start_3</b></td><td>%i</td></tr>\n",mabore.mbr_part_3.part_start);
    fprintf(fp,"<tr><td><b>part_size_3</b></td><td>%i</td></tr>\n",mabore.mbr_part_3.part_size);
    fprintf(fp,"<tr><td><b>part_name_3</b></td><td>%s</td></tr>\n",mabore.mbr_part_3.part_name);

    fprintf(fp,"<tr><td><b>part_status_4</b></td><td>%s</td></tr>\n",mabore.mbr_part_4.part_status);
    fprintf(fp,"<tr><td><b>part_type_4</b></td><td>%c</td></tr>\n",mabore.mbr_part_4.part_type);
    fprintf(fp,"<tr><td><b>part_fit_4</b></td><td>%c</td></tr>\n",mabore.mbr_part_4.part_fit);
    fprintf(fp,"<tr><td><b>part_start_4</b></td><td>%i</td></tr>\n",mabore.mbr_part_4.part_start);
    fprintf(fp,"<tr><td><b>part_size_4</b></td><td>%i</td></tr>\n",mabore.mbr_part_4.part_size);
    fprintf(fp,"<tr><td><b>part_name_4</b></td><td>%s</td></tr>\n",mabore.mbr_part_4.part_name);

    fprintf(fp,"</table>>];}\n");
    fclose ( fp );

    system("dot -Tpng MBR.dot -o mbr.png");
    system("gnome-open mbr.png");


}

void ReporteDisk(struct MBR mabore){
    FILE *fp;
 	fp = fopen ( "disk.dot", "w+" );
    fprintf(fp," digraph {\n");

    /** Acá debo recorrer el mbr para graficar las particiones del disco
        - Tengo que agregar la llamada del reporte con el comando
    */

    fprintf(fp,"}\n");
    fclose ( fp );
    system("dot -Tpng disk.dot -o disk.png");
    system("gnome-open disk.png");


}





