#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <fcntl.h>

struct {
    int start;
    int end;
    int value;
} result;

int main(int argc, char *argv[]) {
    int pid, status, size;
    char down[12], up[12], procNumb[12], buf[sizeof(result)];

    for (int x = 0; x < argc; x++) {
        printf("%d: %s\n", x, argv[x]);
    }
    printf("argc %d Liczba procesów %d\n", argc, argc - 2);
    size = (atoi(argv[2]) - atoi(argv[1])) / atoi(argv[3]);
    for (int y = 1; y <= atoi(argv[3]); y++) {
        if (fork() == 0) {
            sprintf(down, "%d", atoi(argv[1]) + (y - 1) * size + 1);
            sprintf(up, "%d", atoi(argv[1]) + y * size);
            sprintf(procNumb, "%d", y);
            execl("./Inner", down, up, procNumb, NULL);
        }
    }
    for (int j = 0; j < atoi(argv[3]); j++) {
        pid = wait(&status);
        printf("Proces nr %d o pid %d zakonczony status: %d\n", j + 1, pid, WEXITSTATUS(status));
    }
    int file = open("/home/tobiasz/Pulpit/studia/Programowanie współbierzne/lab3/block.bin", O_RDONLY);
    if(file<0) {
        printf("Nie udało się otworzyć pliku\n");
        return -1;
    }
    do {
        file = read(file,buf, sizeof(result));
        printf("%s",buf);
    } while(file > 0);

}