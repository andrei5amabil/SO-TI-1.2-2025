#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <time.h>

typedef struct{
    int id;
    char user[1024];
    double longi;
    double lati;
    char clue[1024];
    int value;
} treasure;

char* create_filepath(char* dir, const char* file){
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
    int bytes_printed;

    if(fd == 1){
        bytes_printed = snprintf(buffer, sizeof(buffer), "%d", t->id);
        write(fd, "id: ", 4);
        write(fd, buffer, bytes_printed);
        write(1, "\n", 1);

        write(fd, "user: ", 7);
        write(fd, t->user, sizeof(t->user));

        bytes_printed = snprintf(buffer, sizeof(buffer), "%f", t->longi);
        write(fd, "longitude: ", 12);
        write(fd, buffer, bytes_printed);
        write(1, "\n", 1);

        bytes_printed = snprintf(buffer, sizeof(buffer), "%f", t->lati);
        write(fd, "latitude: ", 11);
        write(fd, buffer, bytes_printed);
        write(1, "\n", 1);

        write(fd, "clue: ", 7);
        write(fd, t->clue, sizeof(t->clue));

        bytes_printed = snprintf(buffer, sizeof(buffer), "%d", t->value);
        write(fd, "value: ", 8);
        write(fd, buffer, bytes_printed);
        write(1, "\n", 1);
    }
    else{
        write(fd, &t->id, sizeof(t->id));
        write(fd, t->user, sizeof(t->user));
        write(fd, &t->longi, sizeof(t->longi));
        write(fd, &t->lati, sizeof(t->lati));
        write(fd, t->clue, sizeof(t->clue));
        write(fd, &t->value, sizeof(t->value));
    }
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
        read(fd, &t->id, sizeof(t->id));
        read(fd, t->user, sizeof(t->user));
        read(fd, &t->longi, sizeof(t->longi));
        read(fd, &t->lati, sizeof(t->lati));
        read(fd, t->clue, sizeof(t->clue));
        read(fd, &t->value, sizeof(t->value));
    }
    return t;
}

void read_all_treasures(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    
    treasure t;
    while (read(fd, &t.id, sizeof(t.id)) > 0) {

        read(fd, t.user, sizeof(t.user));
        read(fd, &t.longi, sizeof(t.longi));
        read(fd, &t.lati, sizeof(t.lati));
        read(fd, t.clue, sizeof(t.clue));
        read(fd, &t.value, sizeof(t.value));

        write_treasure(&t, 1);
        write(1,"\n",1);
    }
    
    close(fd);
}

void read_specific_treasure(const char* filename, int search_id) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    
    treasure t;
    while (read(fd, &t.id, sizeof(t.id)) > 0) {
        
        read(fd, t.user, sizeof(t.user));
        read(fd, &t.longi, sizeof(t.longi));
        read(fd, &t.lati, sizeof(t.lati));
        read(fd, t.clue, sizeof(t.clue));
        read(fd, &t.value, sizeof(t.value));

        if(t.id == search_id){
            write_treasure(&t, 1);
            break;
        }
    }
    
    close(fd);
}

void remove_treasure(const char* filename, char* hunt, int id) {
    int fd = open(filename, O_RDONLY);

    char* aux_path = create_filepath(hunt, "aux");
    int tmp_fd = open(aux_path, O_WRONLY | O_CREAT | O_TRUNC, S_IXUSR | S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    if (tmp_fd == -1) {
        perror("Error opening file");
        return;
    }
    
    treasure t;
    while (read(fd, &t.id, sizeof(t.id)) > 0) {

        read(fd, t.user, sizeof(t.user));
        read(fd, &t.longi, sizeof(t.longi));
        read(fd, &t.lati, sizeof(t.lati));
        read(fd, t.clue, sizeof(t.clue));
        read(fd, &t.value, sizeof(t.value));

        write_treasure(&t, 1);
        if(t.id != id) write_treasure(&t, tmp_fd);
        write(1,"\n",1);
    }

    read_all_treasures(aux_path);

    remove(filename);
    rename(aux_path, filename);

    close(fd);
    close(tmp_fd);
}

int is_dir(char* dirname){
    struct stat dirstat;
    stat(dirname, &dirstat);
    return S_ISDIR(dirstat.st_mode);
}

int is_id(char* id){
    for(int i = 0; i < strlen(id); i++){
        if(!isdigit(id[i])) return 0;
    }
    return 1;
}

void init_hunt(char* dirname){
    mkdir(dirname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);

    char* treasurespath = create_filepath(dirname, "treasures");
    open(treasurespath, O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);
    free(treasurespath);

    char* logpath = create_filepath(dirname, "logged_hunt.txt");
    open(logpath, O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);
    free(logpath);
}

int is_unique_id(char* filename, int id){
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(-1);
    }

    treasure t;
    while (read(fd, &t.id, sizeof(t.id)) > 0) {

        read(fd, t.user, sizeof(t.user));
        read(fd, &t.longi, sizeof(t.longi));
        read(fd, &t.lati, sizeof(t.lati));
        read(fd, t.clue, sizeof(t.clue));
        read(fd, &t.value, sizeof(t.value));

        if(id == t.id){
            close(fd);
            return 0;
        }
    }
    
    close(fd);
    return 1;
}

int unique_id(char* filename){
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(-1);
    }

    int uniq_id = 0;
    int size = 8;
    int index = 0;
    int* id_array = (int*)malloc(size*sizeof(int));

    treasure t;
    while (read(fd, &t.id, sizeof(t.id)) > 0) {

        read(fd, t.user, sizeof(t.user));
        read(fd, &t.longi, sizeof(t.longi));
        read(fd, &t.lati, sizeof(t.lati));
        read(fd, t.clue, sizeof(t.clue));
        read(fd, &t.value, sizeof(t.value));

        id_array[index] = t.id;
        index++;
        if(index == size){
            size *= 2;
            id_array = realloc(id_array, sizeof(int)*size);
        }

    }

    for(int i = 0; i < index; i++){
        if(uniq_id == id_array[i]){
            uniq_id++;
            i = 0;
        }
    }

    free(id_array);
    close(fd);
    return uniq_id; 
}

int main(int argc, char **argv){
    
    if(argc < 3){
        perror("args error; proper usage: treasure_manager --opt <hunt_id> <id>");
        exit(-1);
    }

    int s = 0;
    if( !strcmp("--add", argv[1]) ){
        s = 1;
    } else if( !strcmp("--list", argv[1]) ){
        s = 2;
    } else if( !strcmp("--view", argv[1]) ){
        s = 3;
    } else if( !strcmp("--remove_treasure", argv[1]) ){
        s = 4;
    } else if( !strcmp("--remove_hunt", argv[1]) ){
        s = 5;
    } else{
        perror("no valid operations detected\nvalid operations:\n--add <hunt_id>\n--list <hunt_id>\n--view <hunt_id> <id>\n--remove_treasure <hunt_id> <id>\n--remove_hunt <hunt_id>");
        exit(-1);
    }

    char* filepath = create_filepath(argv[2], "treasures");
    
    switch(s){
        case 1: //add case
            
            if(!is_dir(argv[2])){
                init_hunt(argv[2]);
            }

            int fd = open(filepath, O_WRONLY | O_APPEND);
            if(fd == -1){
                perror("in add: err opening treasures file");
                exit(-1);
            }

            treasure* t = get_treasure_data(0);
            if(!is_unique_id(filepath, t->id)){
                perror("the id provided already has an associated treasure;");
                write(1, "one valid id is: ", 17);
                char buffer[64];
                //create unique_id
                int x = unique_id(filepath);
                int bytes_printed = snprintf(buffer, sizeof(buffer), "%d", x);
                write(1, buffer, bytes_printed);
                write(1, "\n", 1);
                exit(-1);
            }
            write_treasure(t, fd);

            close(fd);

            break;
        case 2: //list case

            if(!is_dir(argv[2])){
                perror("not an existing hunt; you can add a hunt with treasure_manager --add <hunt_id>");
                exit(-1);
            }

            write(1, argv[2], strlen(argv[2]));
            write(1, "\n", 1);

            struct stat hunt_stat;
            stat(argv[2], &hunt_stat);
            char buffer[64];
            int bytes = snprintf(buffer, sizeof(buffer), "%ld", hunt_stat.st_size);
            write(1, "size: ", 6);
            write(1, buffer, bytes);
            write(1, " bytes\n", 7);

            write(1, "Last modification: ", 19);
            write(1, ctime(&hunt_stat.st_mtime), strlen(ctime(&hunt_stat.st_mtime)));
            write(1, "\n", 1);

            read_all_treasures(filepath);

            break;
        case 3: //view case

            if(!is_dir(argv[2])){
                perror("not an existing hunt; you can add a hunt with treasure_manager --add <hunt_id>");
                exit(-1);
            }

            if(argc < 4){
                perror("no treasure id given; please provide a valid treasure id");
                exit(-1);
            }
            read_specific_treasure(filepath, atoi(argv[3]));

            break;
        case 4: //remove_treasure case

            if(!is_dir(argv[2])){
                perror("not an existing hunt; you can add a hunt with treasure_manager --add <hunt_id>");
                exit(-1);
            }

            if(argc < 4){
                perror("no treasure id given; please provide a valid treasure id");
                exit(-1);
            } else if(!is_id(argv[3])){
                perror("not a valid treasure id;");
                exit(-1);
            }
            remove_treasure(filepath, argv[2], atoi(argv[3]));

            break;
        case 5: //remove_hunt case

            if(!is_dir(argv[2])){
                perror("not an existing hunt; you can add a hunt with treasure_manager --add <hunt_id>");
                exit(-1);
            }

            break;
        default:
            break;
    }

    free(filepath);    

    return 0;
}