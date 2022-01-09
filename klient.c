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
#include <pthread.h>
#include <stdbool.h>
//kbhit()
#include <termios.h>


typedef struct dataV {
    pthread_mutex_t *mutex;
    int koniec;
    int pocetRiadkov;
    int pocetStlpcov;
    int krok;
    int *svet;

} DATA;


int *vytvorSvetNahodne(int pocetRiadkov, int pocetStlpcov);

void zobrazSvet(int pocetRiadkov, int PocetStlpcov, int *pole);

int spocitajSusedov(int pocetStlpcov, int x, int y, int *pole);

int *urobKrok(int pocetRiadkov, int pocetStlpcov, int *pole);

int *vytvorSvetManualne(int pocetRiadkov, int pocetStlpcov);

void zapisHruDoSuboru(int pocetRiadkov, int pocetStlpcov, int *pole);

static void *ovladanie(void *data);

static void *simuluj(void *data);

int posliVolbuNacitania(int volbaNacitania, int sockfd);

int *spojenieZoServerom(int pocetArgumentov, char *nazovProgramu,char *menoServera, char *port, int volbaNacitanie);

void posliSubor(FILE *subor, int sockfd);

int *precitajSubor(int sockfd);

int stlpec;
int riadok;

int mainKlient(int argc, char *argv[]) {
    srand(time(NULL));
    int pocetRiadkov;
    int pocetStlpcov;
    int volbaGenerovania;
    int volbaNacitanie = 0;
    int *svet = NULL;

    printf("------Hra zivot-----\n");
    printf("Chcete nacitat svet z poslednej zvolenej hry?\n");
    printf("Ak ano stlacte 1 ak nie stlacte 0\n");
    scanf("%d", &volbaNacitanie);

    if (volbaNacitanie == 1) {
        svet = spojenieZoServerom(argc, argv[0], argv[2], argv[3], volbaNacitanie);
        pocetStlpcov = stlpec;
        pocetRiadkov = riadok;
    } else {
        printf("Zadajte pocet riadkov svetu: ");
        scanf("%d", &pocetRiadkov);
        printf("Zadajte pocet stlpcov svetu: ");
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
            svet = vytvorSvetManualne(pocetRiadkov, pocetStlpcov);
            zobrazSvet(pocetRiadkov, pocetStlpcov, svet);
            zapisHruDoSuboru(pocetRiadkov, pocetStlpcov, svet);
            spojenieZoServerom(argc, argv[0], argv[2], argv[3],volbaNacitanie);
        } else {
            svet = vytvorSvetNahodne(pocetRiadkov, pocetStlpcov);
            zobrazSvet(pocetRiadkov, pocetStlpcov, svet);
            //znizujeme pocet riadkov na spravny zapis svetu do suboru
            zapisHruDoSuboru(pocetRiadkov, pocetStlpcov, svet);
            spojenieZoServerom(argc, argv[0], argv[2], argv[3], volbaNacitanie);
        }
    }
    int volbaKroky;
    printf("Zvolte si ci chcete zacat od nejakeho kroku\n");
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

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    DATA dataV = {&mutex, 0, pocetRiadkov, pocetStlpcov, krok, svet};

    pthread_t hra;
    pthread_create(&hra, NULL, simuluj, &dataV);

    pthread_t pouzivatel;
    pthread_create(&pouzivatel, NULL, ovladanie, &dataV);

    pthread_join(hra, NULL);
    pthread_join(pouzivatel, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
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
}

void changemode(int dir) {
    static struct termios oldt, newt;

    if (dir == 1) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

static void *ovladanie(void *data) {
    DATA *dataV = data;
    int pom = 0;
    int koniec = 0;
    while (koniec == 0) {
        changemode(1);
        if (kbhit() == 1) {
            printf("Simulacia bola v tomto kroku prerusena\n");
            pthread_mutex_lock(dataV->mutex);
            dataV->koniec = 1;
            koniec = 1;
        } else {
            pom++;
        }
        changemode(0);
        pthread_mutex_unlock(dataV->mutex);
    }
    return NULL;
}

static void *simuluj(void *data) {
    DATA *dataV = data;
    int *novaSimulacia;
    printf("Vlakno zacina simulovat\n");
    int *svet = dataV->svet;
    zobrazSvet(dataV->pocetRiadkov, dataV->pocetStlpcov, svet);
    printf("------------------------\n");
    int koniec = 0;
    int pocitadloKrokov = 0;
    while (koniec == 0) {
        pthread_mutex_lock(dataV->mutex);
        novaSimulacia = urobKrok(dataV->pocetRiadkov, dataV->pocetStlpcov, svet);
        svet = novaSimulacia;
        if (dataV->krok <= pocitadloKrokov && dataV->koniec == 0) {
            zobrazSvet(dataV->pocetRiadkov, dataV->pocetStlpcov, svet);
            printf("Toto bol %d. krok.\n", pocitadloKrokov);
            printf("Ak chcete vypnut simulaciu stlacte lubovolnu klavesu a potvrdte enterom.\n");
            printf("------------------------\n");
            usleep(2000000);
        }
        koniec = dataV->koniec;
        dataV->svet = svet;
        pthread_mutex_unlock(dataV->mutex);
        usleep(200000);
        pocitadloKrokov++;
    }

    free(dataV->svet);
    return NULL;
}

void zobrazSvet(int pocetRiadkov, int pocetStlpcov, int *pole) {
    for (int y = 1; y < pocetRiadkov - 1; ++y) {
        for (int x = 1; x < pocetStlpcov - 1; ++x) {
            printf("%d", *(pole + y * pocetStlpcov + x));
        }
        printf("\n");
    }
}

void zapisHruDoSuboru(int pocetRiadkov, int pocetStlpcov, int *pole) {
    FILE *subor;
    subor = fopen("vystup.txt", "w");
    if (subor == NULL) {
        printf("Subor sa nenasiel\n");
        exit(1);
    }

    printf("Zapisuje sa do suboru\n");
    fprintf(subor, "%d", (pocetRiadkov-2));
    fprintf(subor, "\n");
    fprintf(subor, "%d", (pocetStlpcov-2));
    fprintf(subor, "\n");
    char medzera = ' ';
    for (int y = 1; y < pocetRiadkov - 1; ++y) {
        for (int x = 1; x < pocetStlpcov - 1; ++x) {
            int cislo = *(pole + y * pocetStlpcov + x);
            fprintf(subor, "%d", cislo);
            fprintf(subor, "%c", medzera);
        }
        fprintf(subor, "\n");
    }
    fclose(subor);
}

int *vytvorSvetNahodne(int pocetRiadkov, int pocetStlpcov) {
    printf("Vytvori sa svet nahodne \n");
    printf("Pocet riadkov: %d\n", (pocetRiadkov-2));
    printf("Pocet stlpcov: %d\n", (pocetStlpcov-2));

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
    while (koniecZadavania == false) {
        printf("Zvolte si x-ovu suradnicu bodu(minimalna hodnota moze byt 1 a maximalna: %d\n", pocetRiadkov - 2);
        scanf("%d", &x);
        if ((x >= 0) && (x < pocetRiadkov)) {
            printf("Zvolte si y-ovu suradnicu bodu(minimalna hodnota moze byt 1 a maximalna: %d\n", pocetStlpcov - 2);
            scanf("%d", &y);
            if ((y >= 0) && (y < pocetStlpcov)) {
                for (int i = 1; i < pocetRiadkov - 1; ++i) {
                    for (int j = 1; j < pocetStlpcov - 1; ++j) {
                        *(pole + y * pocetStlpcov + x) = 1;
                    }
                }
            } else {
                printf("Zadali ste neplatnu suradnicu y. \n");
            }
        } else {
            printf("Zadali ste neplatnu suradnicu x. \n");
        }
        printf("Zadajte 0 ak chcete skoncit so zadavanim suradnic alebo zadajte ine cislo ak chcete pokracovat\n");
        scanf("%d", &volbaKoniec);
        if (volbaKoniec == 0) {
            koniecZadavania = true;
        } else {
            koniecZadavania = false;
        }
    }
    return pole;
}

int spocitajSusedov(int pocetStlpcov, int x, int y, int *pole) {
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
    for (int y = 1; y < pocetRiadkov - 1; ++y) {
        for (int x = 1; x < pocetStlpcov - 1; ++x) {
            int zivychSusedov = spocitajSusedov(pocetStlpcov, x, y, pole);
            int bunka = *(pole + y * pocetStlpcov + x);

            if ((zivychSusedov == 1 || zivychSusedov == 0) && bunka == 1) {
                *(pole + y * pocetStlpcov + x) = 0;
            } else if (zivychSusedov >= 4 && bunka == 1) {
                *(pole + y * pocetStlpcov + x)= 0;
            } else if ((zivychSusedov == 2  || zivychSusedov == 3) && bunka == 1) {
                *(pole + y * pocetStlpcov + x)= 1;
            } else if (zivychSusedov == 3 && bunka == 0) {
                *(pole + y * pocetStlpcov + x)= 1;
            }
        }
    }
    return pole;

}

int *spojenieZoServerom(int pocetArgumentov, char *nazovProgramu, char *menoServera, char *port, int volbaNacitanie) {
    int sockfd;
    int *svetZoSuboru;
    struct sockaddr_in serv_addr;
    FILE *subor;
    char *nazovSuboru = "vystup.txt";
    struct hostent *server;

    if (pocetArgumentov < 3) {
        fprintf(stderr, "Malo argumetov v programe s nazvom: %s .\n", nazovProgramu);
        exit(1);
    }
    server = gethostbyname(menoServera);
    if (server == NULL) {
        fprintf(stderr, "Takyto host neeexsituje.\n");
        exit(1);
    }


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(port));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Chyba pri vytvarani socketu");
        exit(1);
    }
    printf("Socket vytvoreny.\n");


    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Nepodarilo sa pripojit na zadanu adresu");
        exit(1);
    }
    printf("Pripojeny k serveru.\n");

    if (volbaNacitanie == 1) {
        posliVolbuNacitania(1, sockfd);
        svetZoSuboru = precitajSubor(sockfd);
        return svetZoSuboru;
    } else {
        posliVolbuNacitania(0, sockfd);
        subor = fopen(nazovSuboru, "r");
        if (subor == NULL) {
            perror("Chyba pri citani suboru\n");
            exit(1);
        }
        posliSubor(subor, sockfd);
        printf("Subor sa poslal uspesne\n");
    }
    close(sockfd);
    printf("Odpojeny zo serveru");
    return NULL;
}

void posliSubor(FILE *subor, int sockfd) {
    char data[1024] = {0};
    while (fgets(data, 1024, subor) != NULL) {
        if (send(sockfd, data, sizeof(data), 0) == -1) {
            perror("Chyba pri posielani suboru\n");
            exit(1);
        }
        bzero(data, 1024);
    }
}

int *precitajSubor(int sockfd) {
    int *pole;
    int n;
    char *cislo;
    FILE *subor;
    char *nazovSuboru = "vystup.txt";
    char buffer[1024];
    subor = fopen(nazovSuboru, "w");
    if (subor == NULL) {
        perror("Chyba pri vytvarani suboru\n");
        exit(1);
    }
    int pocitadlo = 0;
    int pocetRiadkov = 0;
    int pocetStlpcov = 0;
    int nacitaneCislo;
    int x = 0;
    int y = 1;
    while (1) {
        n = recv(sockfd, buffer, 1024, 0);
        if (n <= 0) {
            break;
        }
        fprintf(subor, "%s", buffer);

        if (pocitadlo == 0) {
            pocetRiadkov = atoi(buffer);
            printf("Pocet riadkov je: %d\n", pocetRiadkov);
            pocetRiadkov+=2;
            riadok = pocetRiadkov;
        } else if (pocitadlo == 1) {
            pocetStlpcov = atoi(buffer);
            printf("Pocet stlpcov je: %d\n", pocetStlpcov);
            pocetStlpcov+=2;
            stlpec = pocetStlpcov;
            pole = calloc(pocetRiadkov * pocetStlpcov, sizeof(int));
        } else {
            cislo = strtok(buffer, " ");
            while (cislo != NULL) {
                x++;
                nacitaneCislo = atoi(cislo);
                *(pole + y * pocetStlpcov + x) = nacitaneCislo;
                cislo = strtok(NULL, " ");
                if (x == (pocetStlpcov - 2)) {
                    x = 0;
                    y++;
                    break;
                }
            }
        }
        bzero(buffer, 1024);
        pocitadlo++;
    }
    zobrazSvet(pocetRiadkov, pocetStlpcov, pole);
    return pole;
}

int posliVolbuNacitania(int volbaNacitania, int sockfd) {
    printf("Posielam poziadavku na cinnost %d serveru\n", volbaNacitania);
    int m = write(sockfd, &volbaNacitania, sizeof(volbaNacitania));
    if (m < 0) {
        perror("Chyba pri citani zo soketu\n");
        return 6;
    }
    return 0;
}