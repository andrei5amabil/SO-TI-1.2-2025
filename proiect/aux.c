#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

typedef struct{
    int id;
    char user[1024];
    double longi;
    double lati;
    char clue[1024];
    int value;
} treasure;


int main(void){
    int fd = open("hunt1/treasures", O_RDWR | O_TRUNC);
    if(fd == -1){
        perror("plm");
        return 1;
    }
    
    treasure t = {
        1,
        "andreiul",
        4.76,
        6.99,
        "tetoooo",
        31
    };

    write(fd, &t.id, sizeof(t.id));
    write(fd, t.user, sizeof(t.user));
    write(fd, &t.longi, sizeof(t.longi));
    write(fd, &t.lati, sizeof(t.lati));
    write(fd, t.clue, sizeof(t.clue));
    write(fd, &t.value, sizeof(t.value));

    close(fd);
    return 0;
}