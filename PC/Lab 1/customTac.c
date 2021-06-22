#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> 
#include <stdio.h>

int main(int argc, char **argv) {
    int sursa;
    int coppy;
    int len = 0;
    char buff[1024];
    sursa = open(argv[1], O_RDONLY);
    if(sursa < 0) {
        write(1, "Eroare la deschidere fisier\n", 35);
        return 0;
    }

    lseek(sursa, 0, SEEK_SET);
    coppy = read(sursa, buff, sizeof(buff))
    printf("%d", coppy);
    while(coppy = read(sursa, buff, sizeof(buff))) {
        if(coppy < 0) {
            write(1, "Eroare la deschidere fisier\n", 35);
            return 0;
        }
        len++;
    }
    lseek(sursa, -1, SEEK_END);
    for(int i = 0; i < len; i++) {
        coppy = read(sursa, buff, sizeof(buff));
        if(coppy < 0) {
            write(1, "Eroare la deschidere fisier\n", 35);
            return 0;
        }
        len += coppy;
        write(1, buff, coppy);
        lseek(sursa, -(i+1)*len-1, SEEK_END);
    }
    close(sursa);
    return 0;
}