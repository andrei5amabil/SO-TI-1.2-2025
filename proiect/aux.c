#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

int main(void){
    int id;
    char user[1024];
    float longi;
    float lati;
    char clue[1024];
    int value;

    printf("id: ");
    fflush(stdout);

    char buffer[1024];
    int bytes_read = read(0, buffer, sizeof(buffer)-1);
    buffer[bytes_read] = '\0';
    id = atoi(buffer);
    printf("%d\n", id);
    return 0;
}