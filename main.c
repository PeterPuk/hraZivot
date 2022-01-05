#include <stdio.h>
#include "klient.h"
#include "server.h"
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
int main(int argc, char* argv[]) {
    printf("Som v main\n");
    mainKlient(argc,argv);

}
