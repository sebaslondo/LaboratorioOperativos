#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procesos(char pid[200]);
void procesos_report(char pid[200],char archivo[1024]);
char* substring(char string[1024],int inicio, int fin);

int main (int argc,char **argv)
{
    int c = 2;

    if(strcmp(argv[1], "-l") == 0){
        while(c < argc){
            printf("Pid: %s\n",argv[c]);
            procesos(argv[c]);
            c++;
        }
    }
    else if(strcmp(argv[1], "-r") == 0){
        //psinfo-report-10898-1342.info
        char archivos[1024];
        strcpy(archivos,"psinfo-report");
        while(c < argc){
            strcat(archivos, "-");
            strcat(archivos, argv[c]);
            c++;
        }
        strcat(archivos, ".info");

        //Crear archivo
        FILE *fichero;
        fichero = fopen(archivos, "w+");
        fclose(fichero);

        c = 2;
        while(c < argc){
            procesos_report(argv[c],archivos);
            c++;
        }
        printf("Archivo de salida generado: %s\n",archivos);
    }
    else if(argc == 2){
        procesos(argv[1]);
    }
    else{
        printf("Parece que el numero de parametros es incorrecto, o esta ingresando una opcion que no es permitida\n");
    }
}

char* substring(char* string,int inicio, int fin){
    char *substring;
    //Initial memory allocation
    substring = (char *) malloc(sizeof(char)*fin+1);

    int c = 0;
    while (c < fin){
        substring[c] = string[inicio + c];
        c++;
    }
    return substring;
}

void procesos(char pid[200]){
    //Archivo
    FILE *fichero;
    char cadena[200];
    strcpy(cadena, "/proc/");
    strcat(cadena, pid);
    strcat(cadena, "/status");
    fichero = fopen(cadena, "r");

    if (fichero == NULL){
        printf("\nError, parece que este proceso no existe \n\n");
        return;
    }

    char linea[1024];
    char sub[1024],resto[1024],vacio[1024];
    while(fgets(linea, 1024, (FILE*) fichero)) {
        strcpy(sub,substring(linea,0,27));
        //Name:
        if (strncmp(sub, "Name:", 5)==0){
            strcpy(resto,substring(linea,5,sizeof(linea)));
            printf("El nombre del proceso es: %s", resto);
        }
        //State:
        else if (strncmp(sub, "State:", 6)==0){
            strcpy(resto,substring(linea,6,sizeof(linea)));
            printf("El estado del proceso es: %s", resto);
        }
        //VmSize:
        else if (strncmp(sub, "VmSize:", 7)==0){
            strcpy(resto,substring(linea,7,sizeof(linea)));
            printf("Tamaño total de la imagen de memoria: %s", resto);
        }
        //VmExe:
        else if (strncmp(sub, "VmExe:", 6)==0){
            strcpy(resto,substring(linea,6,sizeof(linea)));
            printf("\tTamaño de la memoria en la región TEXT: %s", resto);
        }
        //VmData:
        else if (strncmp(sub, "VmData:", 7)==0){
            strcpy(resto,substring(linea,7,sizeof(linea)));
            printf("\tTamaño de la memoria en la región DATA: %s", resto);
        }
        //VmStk:
        else if (strncmp(sub, "VmStk:", 6)==0){
            strcpy(resto,substring(linea,6,sizeof(linea)));
            printf("\tTamaño de la memoria en la región STACK: %s", resto);
        }
        //voluntary_ctxt_switches: - nonvoluntary_ctxt_switches:
        else if (strncmp(sub, "voluntary_ctxt_switches:", 24)==0){
            strcpy(resto,substring(linea,24,sizeof(linea)));
            printf("Número de cambios de contexto realizados (voluntarios): %s", resto);
        }
        else if (strncmp(sub, "nonvoluntary_ctxt_switches:", 27)==0){
            strcpy(resto,substring(linea,27,sizeof(linea)));
            printf("Número de cambios de contexto realizados (no voluntarios): %s\n", resto);
        }
        strcpy(sub,vacio);
        strcpy(resto,vacio);
    }
    fclose(fichero);
}
//Funcion de reporte
void procesos_report(char pid[200],char archivo[1024]){
    FILE *fp;
 	fp = fopen (archivo, "a+" );
    fprintf(fp,"Pid: %s\n",pid);

    //Archivo
    FILE *fichero;
    char cadena[200];
    strcpy(cadena, "/proc/");
    strcat(cadena, pid);
    strcat(cadena, "/status");
    fichero = fopen(cadena, "r");

    if (fichero == NULL){
        fprintf(fp,"\nError, parece que este proceso no existe \n\n");
        return;
    }

    char linea[1024];
    char sub[1024],resto[1024],vacio[1024];
    while(fgets(linea, 1024, (FILE*) fichero)) {
        strcpy(sub,substring(linea,0,27));
        //Name:
        if (strncmp(sub, "Name:", 5)==0){
            strcpy(resto,substring(linea,5,sizeof(linea)));
            fprintf(fp,"El nombre del proceso es: %s", resto);
        }
        //State:
        else if (strncmp(sub, "State:", 6)==0){
            strcpy(resto,substring(linea,6,sizeof(linea)));
            fprintf(fp,"El estado del proceso es: %s", resto);
        }
        //VmSize:
        else if (strncmp(sub, "VmSize:", 7)==0){
            strcpy(resto,substring(linea,7,sizeof(linea)));
            fprintf(fp,"Tamaño total de la imagen de memoria: %s", resto);
        }
        //VmExe:
        else if (strncmp(sub, "VmExe:", 6)==0){
            strcpy(resto,substring(linea,6,sizeof(linea)));
            fprintf(fp,"\tTamaño de la memoria en la región TEXT: %s", resto);
        }
        //VmData:
        else if (strncmp(sub, "VmData:", 7)==0){
            strcpy(resto,substring(linea,7,sizeof(linea)));
            fprintf(fp,"\tTamaño de la memoria en la región DATA: %s", resto);
        }
        //VmStk:
        else if (strncmp(sub, "VmStk:", 6)==0){
            strcpy(resto,substring(linea,6,sizeof(linea)));
            fprintf(fp,"\tTamaño de la memoria en la región STACK: %s", resto);
        }
        //voluntary_ctxt_switches: - nonvoluntary_ctxt_switches:
        else if (strncmp(sub, "voluntary_ctxt_switches:", 24)==0){
            strcpy(resto,substring(linea,24,sizeof(linea)));
            fprintf(fp,"Número de cambios de contexto realizados (voluntarios): %s", resto);
        }
        else if (strncmp(sub, "nonvoluntary_ctxt_switches:", 27)==0){
            strcpy(resto,substring(linea,27,sizeof(linea)));
            fprintf(fp,"Número de cambios de contexto realizados (no voluntarios): %s\n", resto);
        }
        strcpy(sub,vacio);
        strcpy(resto,vacio);
    }
    fclose(fichero);
    fclose(fp);
}