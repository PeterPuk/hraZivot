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
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


typedef struct dataV {
    pthread_mutex_t *mutex;
    int koniec;
    int pocetRiadkov;
    int pocetStlpcov;
    int poradoveCislo;
    int volbaSubor;
    int krok;
    int *svet;

} DATA;


int *vytvorSvetNahodne(int pocetRiadkov, int pocetStlpcov);
void zobrazSvet(int pocetRiadkov, int PocetStlpcov, int *pole);
int spocitajSusedov(int pocetRiadkov, int pocetStlpcov, int x, int y, int *pole);
int *urobKrok(int pocetRiadkov, int pocetStlpcov, int *pole);
int *vytvorSvetManualne(int pocetRiadkov, int pocetStlpcov);
void zapisHruDoSuboru(int pocetRiadkov, int pocetStlpcov, int *pole, int poradoveCislo);
int *nacitajHruZoSuboru(int pocetRiadkov, int pocetStlpcov);
static void *ovladanie(void *data);

static void *simuluj(void *data);


int main(int argc, char *argv[]) {
    srand(time(NULL));
    int poradoveCisloHry = 1;
    int pocetRiadkov;
    int pocetStlpcov;
    int volbaGenerovania;
    int volbaSubor;
    int koniec;
    int *svet = NULL;
    //zistiStlacenuKlavesu();
    /*int *pole = nacitajHruZoSuboru(3,3);
    zobrazSvet(3,3,pole);*/
    /*printf("Chcete svet zo suboru?\n");
    printf("Ak ano stlacte 1 ak nie stlacte 0\n");
    scanf("%d", &volbaSubor);*/

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
    if (volbaGenerovania == 0) {
        printf("volba generovania je:%d \n", volbaGenerovania);
        svet = vytvorSvetManualne(pocetRiadkov, pocetStlpcov);
        zobrazSvet(pocetRiadkov, pocetStlpcov, svet);
    } else {
        printf("volba generovania je:%d \n", volbaGenerovania);
        svet = vytvorSvetNahodne(pocetRiadkov, pocetStlpcov);
        zobrazSvet(pocetRiadkov, pocetStlpcov, svet);
    }
    int volbaKroky;
    printf("Zvolte si ci chcete zacat od nejakeho kroku");
    printf("Ak zadate 0- bude sa simulovat od zaciatku\n");
    printf("Ak zadate 1- bude sa simulovat od kroku\n");
    scanf("%d", &volbaKroky);
    int krok = 0;
    if (volbaKroky == 1) {
        printf("Zadajte krok od ktoreho chcete zacat simulovat\n");
        scanf("%d", &krok);

    } else {
        krok = 0;
    }

    /*printf("Chcete zacat simulaciu od nejakeho kroku?\n");
    printf("Ak ano stlacte 1 ak nie stlacte 0\n");
    scanf("%d",&koniec);*/
    //zapisHruDoSuboru(pocetRiadkov,pocetStlpcov,);
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    DATA dataV = {&mutex, 0, pocetRiadkov, pocetStlpcov, poradoveCisloHry, 0, krok, svet};

    pthread_t hra;
    pthread_create(&hra, NULL, simuluj, &dataV);

    pthread_t pouzivatel;
    pthread_create(&pouzivatel, NULL, ovladanie, &dataV);

    pthread_join(hra, NULL);
    pthread_join(pouzivatel, NULL);

    pthread_mutex_destroy(&mutex);

    poradoveCisloHry++;
}
int kbhit(void) {
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET (STDIN_FILENO, &rdfs);

    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);

