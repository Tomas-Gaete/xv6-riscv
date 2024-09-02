#include "kernel/types.h"
#include "user.h"
#include "syscall.h"


int main(int argc, char *argv[]) {
    int ppid = getppid();
    if (argc < 2) {
        printf("Usage: getancestor <n>\n");
        exit(1);
    }
    //int ancestor_0 = getancestor(0); proceso actual
    //int ancestor_1 = getancestor(1); padre del proceso
    int ancestor_2 = getancestor(2);
    int n = atoi(argv[1]);
    int ancestor_pid = getancestor(n);
    printf("Id del Padre del proceso obtenido por getppid: %d\n", ppid);
    printf("Id del Abuelo del proceso: %d\n", ancestor_2);
    printf("Id del Ancestro del proceso de nivel %d: %d\n", n, ancestor_pid);
    exit(0);
}