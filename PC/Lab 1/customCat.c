#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> 
#include <stdio.h>


int main(int argc, char **argv) {
    int sursa;
    int coppy;
    char buff[1024];
    sursa = open(argv[1], O_RDONLY);
    if(sursa < 0) {
        write(1, "Eroare la deschidere fisier\n", 35);
        return 0;
    }

    lseek(sursa, 0, SEEK_SET);
    while(coppy = read(sursa, buff, sizeof(buff))) {
        if(coppy < 0) {
            write(1, "Eroare la deschidere fisier\n", 35);
            return 0;
        }
        write(1, buff, coppy);
    }
    close(sursa);
    return 0;
}