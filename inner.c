#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

struct {
    int start;
    int end;
    int value;
} result;

int first(int n) {
    int i;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0)return (0);
    }
    return (1);
}

void main(int argc, char *argv[]) {
    result.start = atoi(argv[0]);
    result.end = atoi(argv[1]);
    result.value = 0;
    for (int x = 0; x < argc; x++) {
        printf("Proces %s %d: %s\n", argv[2], x, argv[x]);
    }
    for (int i = result.start; i <= result.end; i++) {
        result.value += first(i);
    }

    int file = open("/home/tobiasz/Pulpit/studia/Programowanie współbierzne/lab3/block.bin", O_APPEND | O_WRONLY);
    if(file<0){
        perror("open");
        exit(-1);
    }
    lockf(file, F_LOCK, sizeof(result));
    write(file,&result,sizeof(result));
    lockf(file, F_ULOCK, sizeof(result));
    close(file);
    exit(0);
}

