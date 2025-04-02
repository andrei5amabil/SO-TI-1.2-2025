#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    int fd = open("textfile.txt", O_RDONLY);
    if(fd == -1){
        perror("Error opening file!");
    }
    char buffer[1024];
    if( lseek(fd, 512, SEEK_SET) == -1 ){
        perror("ceva ceva fisiere");
        exit(-1);
    }
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer)-1);
    if(bytes_read == -1){
        perror("big issue bud");
    }
    else if (bytes_read == 0){
        printf("eof\n");
    }
    else {
        buffer[bytes_read] = '\0';
        printf("Read %zd bytes: %s\n", bytes_read, buffer);
    }

    if(close(fd) == -1){
        perror("raghhh");
    }
    return 0;
}