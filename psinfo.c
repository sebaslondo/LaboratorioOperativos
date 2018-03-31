#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procesos(char pid[200]);
void procesos2(char pid[200],char archivo[1024]);

int main (int argc,char **argv)
{
    int c = 2;

    if(strncmp(argv[1], "-l", 2) == 0){
        while(c < argc){
            printf("Pid: %s\n",argv[c]);
            procesos(argv[c]);
            c++;
        }
    }
    else if(strncmp(argv[1], "-r", 2) == 0){
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
            procesos2(argv[c],archivos);
            c++;
        }
    }
    else{
        procesos(argv[1]);
    }
    return 0;
}

void procesos(char pid[200]){

    FILE *fichero;
    char linea[1024];

    //Archivo
    char cadena[200];
    strcpy(cadena, "/proc/");
    strcat(cadena, pid);
    strcat(cadena, "/status");

    fichero = fopen(cadena, "r");

    char sub[1024],resto[1024],vacio[1024];
    int c = 0;

    //Name:
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 5){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-5] = linea[c];
            c++;
        }

        if (strncmp(sub, "Name:", 5)==0){
            printf("El nombre del proceso es: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //State:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 6){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-6] = linea[c];
            c++;
        }

        if (strncmp(sub, "State:", 6)==0){
            printf("El estado del proceso es: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmSize:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 7){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-7] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmSize:", 7)==0){
            printf("Tamaño total de la imagen de memoria: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmExe:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {

        while (c < 6){
            sub[c] = linea[c];
            c++;
        }

        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-6] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmExe:", 6)==0){
            printf("\tTamaño de la memoria en la región TEXT: %s", resto);
        }

        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmData:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 7){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-7] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmData:", 7)==0){
            printf("\tTamaño de la memoria en la región DATA: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmStk:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 6){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-6] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmStk:", 6)==0){
            printf("\tTamaño de la memoria en la región STACK: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //voluntary_ctxt_switches: - nonvoluntary_ctxt_switches:
    fichero = fopen(cadena, "r");
    char total[1024],total2[1024];
    while(fgets(linea, 1024, (FILE*) fichero)) {

        if (strncmp(total2, "voluntary_ctxt_switches:", 24)==0){
            while (c < 27){
                sub[c] = linea[c];
                c++;
            }
            sub[c] = '\0';

            while ( c < sizeof(linea)-950){
                resto[c-27] = linea[c];
                c++;
            }

            if (strncmp(sub, "nonvoluntary_ctxt_switches:", 27)==0){
                strcat(total,resto);
                printf("Número de cambios de contexto realizados (voluntarios - no voluntarios): %s\n", total);
            }
            c = 0;
            strcpy(sub,vacio);
        }
        else{
            while (c < 24){
                sub[c] = linea[c];
                c++;
            }
            sub[c] = '\0';

            while ( c < sizeof(linea)-950){
                resto[c-24] = linea[c];
                c++;
            }

            if (strncmp(sub, "voluntary_ctxt_switches:", 24)==0){
                strcpy(total,resto);
                strcpy(total2,sub);
                strcat(total," - ");
            }
            c = 0;
            strcpy(sub,vacio);
        }
    }
    fclose(fichero);
}






















//segunda funcion
void procesos2(char pid[200],char archivo[1024]){
    FILE *fp;
 	fp = fopen (archivo, "r+" );
    fprintf(fp,"Pid: %s\n",pid);
 	
 	//return;

    FILE *fichero;
    char linea[1024];

    //Archivo
    char cadena[200];
    strcpy(cadena, "/proc/");
    strcat(cadena, pid);
    strcat(cadena, "/status");

    fichero = fopen(cadena, "r");

    char sub[1024],resto[1024],vacio[1024];
    int c = 0;

    //Name:
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 5){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-5] = linea[c];
            c++;
        }

        if (strncmp(sub, "Name:", 5)==0){
            fprintf(fp,"El nombre del proceso es: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //State:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 6){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-6] = linea[c];
            c++;
        }

        if (strncmp(sub, "State:", 6)==0){
            fprintf(fp,"El estado del proceso es: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmSize:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 7){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-7] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmSize:", 7)==0){
            fprintf(fp,"Tamaño total de la imagen de memoria: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmExe:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {

        while (c < 6){
            sub[c] = linea[c];
            c++;
        }

        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-6] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmExe:", 6)==0){
            fprintf(fp,"\tTamaño de la memoria en la región TEXT: %s", resto);
        }

        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmData:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 7){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-7] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmData:", 7)==0){
            fprintf(fp,"\tTamaño de la memoria en la región DATA: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //VmStk:
    fichero = fopen(cadena, "r");
    while(fgets(linea, 1024, (FILE*) fichero)) {
        while (c < 6){
            sub[c] = linea[c];
            c++;
        }
        sub[c] = '\0';

        while ( c < sizeof(linea)-1){
            resto[c-6] = linea[c];
            c++;
        }

        if (strncmp(sub, "VmStk:", 6)==0){
            fprintf(fp,"\tTamaño de la memoria en la región STACK: %s", resto);
        }
        c = 0;
        strcpy(sub,vacio);
    }
    fclose(fichero);

    //voluntary_ctxt_switches: - nonvoluntary_ctxt_switches:
    fichero = fopen(cadena, "r");
    char total[1024],total2[1024];
    while(fgets(linea, 1024, (FILE*) fichero)) {

        if (strncmp(total2, "voluntary_ctxt_switches:", 24)==0){
            while (c < 27){
                sub[c] = linea[c];
                c++;
            }
            sub[c] = '\0';

            while ( c < sizeof(linea)-950){
                resto[c-27] = linea[c];
                c++;
            }

            if (strncmp(sub, "nonvoluntary_ctxt_switches:", 27)==0){
                strcat(total,resto);
                fprintf(fp,"Número de cambios de contexto realizados (voluntarios - no voluntarios): %s\n", total);
            }
            c = 0;
            strcpy(sub,vacio);
        }
        else{
            while (c < 24){
                sub[c] = linea[c];
                c++;
            }
            sub[c] = '\0';

            while ( c < sizeof(linea)-950){
                resto[c-24] = linea[c];
                c++;
            }

            if (strncmp(sub, "voluntary_ctxt_switches:", 24)==0){
                strcpy(total,resto);
                strcpy(total2,sub);
                strcat(total," - ");
            }
            c = 0;
            strcpy(sub,vacio);
        }
    }
    fclose(fichero);
    fclose (fp);
}