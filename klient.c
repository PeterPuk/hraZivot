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

//kniznice potrebne na chod metody kbhit()
#include <termios.h>
#include <sys/time.h>

void zacni(int pocetRiadkov, int pocetStlpcov, int volbaGenerovania);

int *vytvorSvetNahodne(int pocetRiadkov, int pocetStlpcov);

void zobrazSvet(int pocetRiadkov, int PocetStlpcov, int *pole);

int spocitajSusedov(int pocetRiadkov, int pocetStlpcov, int x, int y, int *pole);

int *urobKrok(int pocetRiadkov, int pocetStlpcov, int *pole);

int *vytvorSvetManualne(int pocetRiadkov, int pocetStlpcov);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int pocetRiadkov;
    int pocetStlpcov;
    int volbaGenerovania;
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
    zacni(pocetRiadkov, pocetStlpcov,volbaGenerovania);

}

void zacni(int pocetRiadkov, int pocetStlpcov, int volbaGenerovania) {
    int *svet = calloc(pocetRiadkov * pocetStlpcov, sizeof(int));
    if(volbaGenerovania==1){
        printf("Bunky sa vam nahodne vygeneruju\n");
        svet = vytvorSvetNahodne(pocetRiadkov, pocetStlpcov);
    }else{
        printf("Zvolte si bunky ktore budu zit na zaciatku\n");
        svet = vytvorSvetManualne(pocetRiadkov, pocetStlpcov);
    }
    if (svet == NULL) {
        return;
    }
    zobrazSvet(pocetRiadkov, pocetStlpcov, svet);
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
            if(volbaZnaku==1){
                *(pole + y * pocetStlpcov + x) = 1;
            }else{
                *(pole + y * pocetStlpcov + x) =0;
            }

        }
    }

    return pole;

}

int *vytvorSvetManualne(int pocetRiadkov, int pocetStlpcov){


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
