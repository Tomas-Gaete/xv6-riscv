#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"

int main() {
    char *addr = sbrk(0);  // Obtener la dirección actual del heap
    sbrk(4096);  // Reservar una página
    // Intentar proteger la nueva página
    if (mprotect(addr, 1) == -1) {
        printf("mprotect falló\n");
        exit(1);
    }
    // Intentar escribir en la página protegida
    char *ptr = addr;
    int write_failed = 0;
    if (fork() == 0) {
        // Se intenta escribir
        printf("Memoría original: %d",*ptr);
        *ptr = 'A';  // This should fail if protection is working
        printf("Unexpectedly succeeded in writing to protected memory.\n");
        exit(0);
    } else {
        // Se revisa si falló la escritura 
        int status;
        wait(&status);
        if (status != 0) {
            printf("Funcionó la protección de memoria y no se logró escribir.\n");
            printf("Memoría protegida: %d\n\n",*ptr);
            write_failed = 1;
        } else {
            printf("Falló la protección y se logró escribir.\n");
        }
    }

    // Ahora probamos la funcionalidad de munprotect quitando la protección
    if (write_failed && munprotect(addr, 1) == -1) {
        printf("munprotect falló\n");
        exit(1);
    }

    // Se intenta escribír en la memoria y se observa el nuevo valor
    if (write_failed) {
        printf("Valor de la memoría desprotegida antes: %d\n\n",*ptr);
        *ptr = 'C';  //  'A' retorna 65, 'B' retorna 66 y 'C' 67 y asi sucesivamente.
        printf("Se logró escribir en la memoría luego de retornar los permisos quedando en la memoria el valor correspondiente a la letra 'C': %d\n", *ptr);
    }

    return 0;
}
