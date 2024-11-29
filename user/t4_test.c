#include "kernel/types.h" // for basic types like int
#include "kernel/stat.h"  // for file stats, if needed
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

int main(int argc, char *argv[]){
    char *path = "/file";
    int fd;
    printf("Testeo de funcionalidad de chmod y la nueva lógica de permisos\n");
    printf("==============================================================\n");
    printf("Creación de un archivo:\n");
    fd = open(path, O_CREATE | O_RDWR);
    if (fd < 0)
    {
        printf("Error creando el archivo\n");
        exit(1);
    }
    else
    {
        printf("Correcto!!!\n");
    }
    printf("==============================================================\n");
    printf("Test de escritura:\n");
    fd = open(path, O_RDWR);
    if (write(fd, "Vemos si se escribe o no\n", 25) != 25)
    {
        printf("No se logro escribir en el archivo\n");
        close(fd);
        exit(1);
    }
    close(fd);
    printf("Correcto!!!\n");
    printf("\n");
    printf("==============================================================\n");
    printf("Cambiamos permiso a solo lectura:\n");
    if (chmod(path, 1) < 0)
    {
        printf("Error al cambiar permisos a solo lectura\n");
        exit(1);
    }
    else
    {
        printf("Correcto!!!\n");
    }
    printf("==============================================================\n");
    printf("Probamos escribir en el archivo con solo permisos de lectura\n");
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("No logra escribir como se esperaba\n");
        printf("Correcto!!!\n");
    }
    else
    {
        printf("Falló el permiso y se logro escribir\n");
        close(fd);
    }
    printf("==============================================================\n");
    printf("Cambiamos los permisos a read/write:\n");
    if (chmod(path, 3) < 0)
    {
        printf("No se cambiaron los permisos\n");
        exit(1);
    }
    else
    {
        printf("Correcto!!!\n");
    }
    printf("==============================================================\n");
    printf("Comprobamos si se puede leer y escribir\n");
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("Falló abrir el archivo en modo escritura\n");
        exit(1);
    }
    if (write(fd, "Cambio final!\n", 14) != 14)
    {
        printf("Fallá al escribir\n");
    }
    else
    {
        printf("Correcto!!!\n");
    }
    close(fd);
    printf("==============================================================\n");
    printf("Cambiamos permisos a inmutable\n");
    if (chmod(path, 5) < 0)
    {
        printf("Falló al cambiar permisos\n");
        exit(1);
    }
    else
    {
        printf("Correcto!!!\n");
    }
    printf("==============================================================\n");
    printf("Intentamos acceder el archivo:\n");
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("Correcto!!!\n");
    }
    else
    {
        printf("Falló el modo inmutable permitiendo abrir en modo escritura con permisos de inmutable\n");
        close(fd);
    }
    printf("==============================================================\n");
    printf("Chequeamos la inmutabilidad:\n");
    if (chmod(path, 3) < 0)
    {
        printf("Correcto!!!\n");
    }
    else
    {
        printf("Falló la inmutabilidad\n");
    }
    printf("==============================================================\n");
    printf("Test terminado!\n");  
    exit(0);
}