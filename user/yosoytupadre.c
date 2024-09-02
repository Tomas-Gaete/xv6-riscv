#include "kernel/types.h"
#include "user.h"
#include "syscall.h"


int main(int argc, char *argv[]) {
    int ppid = getppid();
    if (argc < 2) {
        printf("Usage: getancestor <n>\n");
        exit(1);
    }
    int ancestor_0 = getancestor(0);
    int ancestor_1 = getancestor(1);
    int ancestor_2 = getancestor(2);
    int n = atoi(argv[1]);
    int ancestor_pid = getancestor(n);
    printf("Padre del proceso obtenido por getppid: %d\n", ppid);
    printf("Proceso actual: %d\n", ancestor_0);
    printf("Padre del proceso: %d\n", ancestor_1);
    printf("Abuelo del proceso: %d\n", ancestor_2);
    printf("Ancestor PID at level %d: %d\n", n, ancestor_pid);
    exit(0);
}