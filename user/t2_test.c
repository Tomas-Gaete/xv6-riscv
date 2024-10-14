#include <stdio.h>
#include <unistd.h>   // Para fork(), getpid(), sleep()
#include <sys/wait.h> // Para wait()

int main() {
    int num_procesos = 20; // Número de procesos a crear
    pid_t pid;

    for (int i = 0; i < num_procesos; i++) {
        pid = fork();  // Crear un nuevo proceso

        if (pid < 0) {
            // Error al crear el proceso
            printf("Error en fork");
            return 1;
        } else if (pid == 0) {
            // Proceso hijo
            printf("Ejecutando proceso hijo %d con PID %d\n", i + 1, getpid());
            sleep(2);  // Detener el proceso por 2 segundos
            return 0;  // Salir del proceso hijo
        } else {
            // Proceso padre
            // Puedes esperar aquí si quieres que los procesos se ejecuten uno tras otro
            wait(NULL);  // Espera a que termine el proceso hijo actual
        }
    }

    return 0;
}