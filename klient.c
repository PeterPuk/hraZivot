//
// Created by Puky on 28/12/2021.
//
#include "klient.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<ctype.h>
#include <pthread.h>
#include <stdbool.h>
//kniznice potrebne na chod metody kbhit()
#include <termios.h>
#include <sys/time.h>

void zacni(int pocetRiadkov, int pocetStlpcov, int volbaGenerovania,int poradoveCislo,int volbaSubor);

int *vytvorSvetNahodne(int pocetRiadkov, int pocetStlpcov);

void zobrazSvet(int pocetRiadkov, int PocetStlpcov, int *pole);

int spocitajSusedov(int pocetRiadkov, int pocetStlpcov, int x, int y, int *pole);

int *urobKrok(int pocetRiadkov, int pocetStlpcov, int *pole);

int *vytvorSvetManualne(int pocetRiadkov, int pocetStlpcov);

void zapisHruDoSuboru(int pocetRiadkov, int pocetStlpcov, int *pole, int poradoveCislo);

int *nacitajHruZoSuboru(int pocetRiadkov, int pocetStlpcov);

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int poradoveCisloHry = 1;
    int pocetRiadkov;
    int pocetStlpcov;
    int volbaGenerovania;
    int volbaSubor;

    printf("Chcete svet zo soboru?\n");
    printf("Ak ano stlacte 1 ak nie stlacte 0\n");
    scanf("%d", &volbaSubor);

    printf("Zadaj pocet riadkov svetu: ");
    scanf("%d", &pocetRiadkov);
    printf("Zadaj pocet stlpcov svetu: ");
    scanf("%d", &pocetStlpcov);
    printf("-------------------------------\n");
    printf("Zvolte si ci chcete generovat nahodne alebo manualne\n");
    printf("Ak zadate 1- bude sa generovat nahodne\n");
    printf("Ak zadate 0- budete si moct sami zvolit bunky\n");
    printf("-------------------------------\n");
    scanf("%d", &volbaGenerovania);

    pocetRiadkov += 2;
    pocetStlpcov += 2;
    zacni(pocetRiadkov, pocetStlpcov, volbaGenerovania,poradoveCisloHry,volbaSubor);
    /*zapisHruDoSuboru(pocetRiadkov,pocetStlpcov,);*/
    poradoveCisloHry++;
}

void zacni(int pocetRiadkov, int pocetStlpcov, int volbaGenerovania,int poradoveCislo, int volbaSubor) {
    int *svet = calloc(pocetRiadkov * pocetStlpcov, sizeof(int));
    if(volbaSubor==1){
        svet = nacitajHruZoSuboru(pocetRiadkov,pocetStlpcov);

    }
    if (volbaGenerovania == 1 && volbaSubor==0) {
        printf("Bunky sa vam nahodne vygeneruju\n");
        svet = vytvorSvetNahodne(pocetRiadkov, pocetStlpcov);
    } else {
        printf("Zvolte si bunky ktore budu zit na zaciatku\n");
        svet = vytvorSvetManualne(pocetRiadkov, pocetStlpcov);
    }
    if (svet == NULL) {
        return;
    }

    zobrazSvet(pocetRiadkov, pocetStlpcov, svet);
    zapisHruDoSuboru(pocetRiadkov,pocetStlpcov,svet,poradoveCislo);
    for (int i = 0; i < 10; ++i) {
        int *novaSimulacia = urobKrok(pocetRiadkov, pocetStlpcov, svet);
        if (novaSimulacia == NULL)return;
        svet = novaSimulacia;
        zobrazSvet(pocetRiadkov, pocetStlpcov, svet);
    }


}


void zobrazSvet(int pocetRiadkov, int pocetStlpcov, int *pole) {
    for (int y = 0; y < pocetRiadkov; ++y) {
        for (int x = 0; x < pocetStlpcov; ++x) {
            printf("%d", *(pole + y * pocetStlpcov + x));
        }
        printf("\n");
    }
    printf("------------------------\n");
}

void zapisHruDoSuboru(int pocetRiadkov, int pocetStlpcov, int *pole,int poradoveCislo){
    FILE *subor = fopen("vystup.txt","w");
    if(subor == NULL){
        printf("Subor sa nenasiel\n");
        exit(1);
    }
    printf("Zapisuje sa do suboru\n");
    for (int y = 0; y < pocetRiadkov; ++y) {
        for (int x = 0; x < pocetStlpcov; ++x) {
            int cislo = *(pole + y * pocetStlpcov + x);
            fprintf(subor, "%d\n", cislo);

        }
        fprintf(subor, "\n");
    }
    fclose(subor);
}

int *nacitajHruZoSuboru(int pocetRiadkov, int pocetStlpcov){
    int *pole = calloc(pocetRiadkov * pocetStlpcov, sizeof(int));
    FILE *vstup = fopen("vstup.txt","r");
    if(vstup == NULL){
        printf("Subor sa nenasiel\n");
        exit(1);
    }
    int cislo;
    for (int y = 0; y < pocetRiadkov; ++y) {
        for (int x = 0; x < pocetStlpcov; ++x) {



            fscanf(vstup, "%d",&cislo);
            *(pole + y * pocetStlpcov + x) = cislo;

        }

    }




    return pole;
}


int *vytvorSvetNahodne(int pocetRiadkov, int pocetStlpcov) {
    printf("Zaciatok \n");
    printf("Pocet riadkov: %d\n", pocetRiadkov);
    printf("Pocet stlpcov: %d\n", pocetStlpcov);

    int *pole = calloc(pocetRiadkov * pocetStlpcov, sizeof(int));
    if (pole == NULL) {
        return NULL;
    }
    for (int y = 1; y < pocetRiadkov - 1; ++y) {
        for (int x = 1; x < pocetStlpcov - 1; ++x) {
            int volbaZnaku = rand() % 2;
            if (volbaZnaku == 1) {
                *(pole + y * pocetStlpcov + x) = 1;
            } else {
                *(pole + y * pocetStlpcov + x) = 0;
            }

        }
    }

    return pole;

}

int *vytvorSvetManualne(int pocetRiadkov, int pocetStlpcov) {
    int *pole = calloc(pocetRiadkov * pocetStlpcov, sizeof(int));
    if (pole == NULL) {
        return NULL;
    }

    int x, y;
    int volbaKoniec;
    bool koniecZadavania;
    int pocetR, pocetS;
    while (koniecZadavania == false) {


        printf("Zvolte si x-ovu suradnicu bodu(minimalna hodnota moze byt 1 a maximalna: %d\n", pocetRiadkov-2);
        scanf("%d", &x);
        if ((x >= 0) && (x < pocetRiadkov)) {
            printf("Zvolte si y-ovu suradnicu bodu(minimalna hodnota moze byt 1 a maximalna: %d\n", pocetStlpcov-2);
            scanf("%d", &y);
            if ((y >= 0) && (y < pocetStlpcov)) {

                for (int i = 1; i < pocetRiadkov - 1; ++i) {
                    for (int j = 1; j < pocetStlpcov - 1; ++j) {
                        *(pole + y * pocetStlpcov + x) = 1;
                    }
                }
            }else{
                printf("Zadali ste neplatnu suradnicu y. \n");
            }
        }else{
            printf("Zadali ste neplatnu suradnicu x. \n");
        }

        printf("Zadajte 0 ak chcete skoncit so zadavanim suradnic alebo zadajte 1 ak chcete pokracovat\n");
        scanf("%d",&volbaKoniec);
        if(volbaKoniec==0){
            koniecZadavania = true;
        }else{
            koniecZadavania = false;
        }
    }
    return pole;

}

int spocitajSusedov(int pocetRiadkov, int pocetStlpcov, int x, int y, int *pole) {
    int pocet = 0;

    int pivot = y * pocetStlpcov + x;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int pom = *(pole + pivot + (i * pocetStlpcov) + j);
            if (i == 0 && j == 0) {
                if (pom == 1) {
                    pocet--;
                }
            }
            if (pom == 1) {//ak sa nasiel zivi sused
                pocet++;
            }

        }
    }
    return pocet;
}

int *urobKrok(int pocetRiadkov, int pocetStlpcov, int *pole) {
    int *pomPole = calloc(pocetRiadkov * pocetStlpcov, sizeof(int));
    if (pomPole == NULL) {
        return NULL;
    }

    for (int y = 1; y < pocetRiadkov - 1; ++y) {
        for (int x = 1; x < pocetStlpcov - 1; ++x) {
            int zivychSusedov = spocitajSusedov(pocetRiadkov, pocetStlpcov, x, y, pole);
            int bunka = *(pole + y * pocetStlpcov + x);

            if ((zivychSusedov == 1 || zivychSusedov == 0) && bunka == 1) {
                *(pomPole + y * pocetStlpcov + x) = 0;
            } else if (zivychSusedov >= 4 && bunka == 1) {
                *(pomPole + y * pocetStlpcov + x) = 0;
            } else if ((zivychSusedov == 2 || zivychSusedov == 3) && bunka == 1) {
                *(pomPole + y * pocetStlpcov + x) = 1;
            } else if (zivychSusedov == 3 && bunka == 0) {
                *(pomPole + y * pocetStlpcov + x) = 1;
            }

        }
    }
    return pomPole;
}
