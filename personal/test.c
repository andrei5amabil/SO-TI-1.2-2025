#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(void){
    int fd = open("/home/andreiul/facultate/SO1/personal/sample.txt", O_RDWR);
    char* text = NULL;
    read(fd, (void*)text, 10);
    strcat(text,"\0");
    printf("%s\n", text);
    close(fd);
    return 0;
}