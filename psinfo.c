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
        char archivo[1024];
        strcpy(archivo,"psinfo-report");
        while(c < argc){
            strcat(archivo, "-");
            strcat(archivo, argv[c]);
            c++;
        }
        strcat(archivo, ".info");

        //Crear archivo
        FILE *fichero;
        fichero = fopen(archivo, "w+");
        fclose(fichero);

        c = 2;
        while(c < argc){
            procesos2(argv[c],archivo);
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

void procesos2(char pid[200],char archivo[1024]){
    FILE *report;
    printf("%s \n",archivo);
 		
    report = fopen(archivo, "a+"); //parametro para escritura al final y para file tipo texto

    printf("Pid: %s\n",pid);

    fprintf(report,"Pid: %s\n",pid);

    FILE *fichero;
    char linea[1024];
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
            strcpy(cadena,"El nombre del proceso es: ");
            strcat(cadena,resto);
            strcat(cadena,"\n");

            fputs(cadena,report);
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
            strcpy(cadena,"El estado del proceso es: ");
            strcat(cadena,resto);
            strcat(cadena,"\n");

            fputs(cadena,report);
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
            strcpy(cadena,"Tamaño total de la imagen de memoria: ");
            strcat(cadena,resto);
            strcat(cadena,"\n");

            fputs(cadena,report);
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
            strcpy(cadena,"\tTamaño de la memoria en la región TEXT: ");
            strcat(cadena,resto);
            strcat(cadena,"\n");

            fputs(cadena,report);
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
            strcpy(cadena,"\tTamaño de la memoria en la región DATA: ");
            strcat(cadena,resto);
            strcat(cadena,"\n");

            fputs(cadena,report);
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
            strcpy(cadena,"\tTamaño de la memoria en la región STACK: ");
            strcat(cadena,resto);
            strcat(cadena,"\n");

            fputs(cadena,report);
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
                strcpy(cadena,"Número de cambios de contexto realizados (voluntarios - no voluntarios): ");
                strcat(cadena,total);
                strcat(cadena,"\n");

                fputs(cadena,report);
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
    fclose(report);
}