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

char* create_filepath(char* dir, char* file){
    int filepath_len = strlen(dir) + strlen(file) + 2;
    char *filepath = malloc(sizeof(char) * filepath_len);
    if(!filepath){
        perror("malloc err");
        exit(-1);
    }
    snprintf(filepath, filepath_len, "%s/%s", dir, file);
    return filepath;
}

void write_treasure(treasure* t, int fd){
    char buffer[1024];
    int bytes_printed = snprintf(buffer, sizeof(buffer), "%d", t->id);
    write(fd, "id: ", 4);
    write(fd, buffer, bytes_printed);

    write(fd, "user: ", 7);
    write(fd, t->user, sizeof(t->user));

    bytes_printed = snprintf(buffer, sizeof(buffer), "%f", t->longi);
    write(fd, "longitude: ", 12);
    write(fd, buffer, bytes_printed);

    bytes_printed = snprintf(buffer, sizeof(buffer), "%f", t->lati);
    write(fd, "latitude: ", 11);
    write(fd, buffer, bytes_printed);

    write(fd, "clue: ", 7);
    write(fd, t->clue, sizeof(t->clue));

    bytes_printed = snprintf(buffer, sizeof(buffer), "%d", t->value);
    write(fd, "value: ", 8);
    write(fd, buffer, bytes_printed);
}

treasure* get_treasure_data(int fd){
    treasure* t = (treasure*)malloc(sizeof(treasure));

    char buffer[1024];
    int bytes_read;

    if(fd == 0){
        printf("id: ");
        fflush(stdout);
        bytes_read = read(0, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->id = atoi(buffer);

        printf("user: ");
        fflush(stdout);
        bytes_read = read(0, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        strcpy(t->user, buffer);

        printf("longitude: ");
        fflush(stdout);
        bytes_read = read(0, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->longi = atof(buffer);

        printf("latitude: ");
        fflush(stdout);
        bytes_read = read(0, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->lati = atof(buffer);

        printf("clue: ");
        fflush(stdout);
        bytes_read = read(0, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        strcpy(t->clue, buffer);

        printf("value: ");
        fflush(stdout);
        bytes_read = read(0, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->value = atoi(buffer);
    }
    else{
        bytes_read = read(fd, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->id = atoi(buffer);

        bytes_read = read(fd, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        strcpy(t->user, buffer);

        bytes_read = read(fd, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->longi = atof(buffer);

        bytes_read = read(fd, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->lati = atof(buffer);

        bytes_read = read(fd, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        strcpy(t->clue, buffer);

        bytes_read = read(fd, buffer, sizeof(buffer)-1);
        buffer[bytes_read] = '\0';
        t->value = atoi(buffer);
    }
    return t;
}

int main(int argc, char **argv){
    DIR* dirp = opendir(argv[1]);

    if(dirp == NULL){
        perror("not a dir");
        exit(-1);
    }

    struct dirent* huntinfo;

    while( (huntinfo = readdir(dirp)) != NULL ){
        if(  !((strcmp(huntinfo->d_name, ".") == 0) || (strcmp(huntinfo->d_name, "..") == 0))  ){
            printf("%s\n", huntinfo->d_name);
            
            char* filepath = create_filepath(argv[1], huntinfo->d_name);

            struct stat filestat;
            if( stat(filepath, &filestat) == -1 ){
                printf("err\n");
            }

            if(S_ISREG(filestat.st_mode)){
                printf("regular file\n");

                int fd = open(filepath, O_RDONLY);
                if(fd == -1){
                    perror("failed to open");
                }

                char buffer[1024];
                int bufflen = read(fd, buffer, 1023);
                buffer[bufflen] = '\0';
                printf("%s\n", buffer);

                close(fd);

            } else if(S_ISDIR(filestat.st_mode)){
                printf("directory\n");
            }

            free(filepath);
        }
    }

    treasure* t = get_treasure_data(0);

    write_treasure(t,1);

    free(t);

    closedir(dirp);
    return 0;
}