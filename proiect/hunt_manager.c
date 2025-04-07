#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

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
            
            int filepath_len = strlen(argv[1]) + strlen(huntinfo->d_name) + 2;
            char *filepath = malloc(sizeof(char) * filepath_len);
            if(!filepath){
                perror("malloc err");
                exit(-1);
            }
            snprintf(filepath, filepath_len, "%s/%s", argv[1], huntinfo->d_name);

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

    closedir(dirp);
    return 0;
}