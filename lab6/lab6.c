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
    char outname[256];
    strcpy(outname, "out.txt");
    int outfd = open(outname, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
    if( outfd == -1 ){
        perror("error creating out file");
        exit(-1);
    }

    char s[32];
    int len = snprintf(s, sizeof(s), "%d\n", nrcif);
    write(outfd, s, len);

    len = snprintf(s, sizeof(s), "%d\n", filestat.st_uid);
    write(outfd, s, len);

    len = snprintf(s, sizeof(s), "%ld\n", filestat.st_size);
    write(outfd, s, len);

    symlink(outname, "out");

    close(fd);

    close(outfd);
    return 0;
}