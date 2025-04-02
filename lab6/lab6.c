#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    if(argc != 2){
        perror("wrong args");
        exit(-1);
    }
    int fd = open(argv[1], O_RDONLY);
    if( fd == -1 ){
        perror("err opening input file");
        exit(-1);
    }
    char buffer[512];
    int rd_size;
    int nrcif = 0;

    while((rd_size = read(fd, buffer, sizeof(buffer)-1)) > 0){
        buffer[rd_size] = '\0';
        write(1, buffer, rd_size);
        for(int i = 0; i < rd_size; i++){
            if(isdigit(buffer[i])) nrcif++;
        }    
    }

    struct stat filestat;
    stat(argv[1], &filestat);
    int outfd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if( outfd == -1 ){
        perror("error creating out file");
        exit(-1);
    }

    write(outfd, filestat.st_uid, sizeof(nrcif));

    printf("%d\n", nrcif);

    close(fd);
    return 0;
}