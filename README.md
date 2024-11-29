Informe Tarea 4
==================

Primero se creo y agregó el archivo t4_test.c al makefile para ser llamado para testear los modos de permisos y la llamada chmod.

Luego se observó en file.h la estructura general de los inodos y se agregó el int permissions a su estructura para manejar los modos asignados con el nuevo código.

Luego se creó la llamada al sistema chmod para cambiar los permisos

Primero se definio lógica que utilizaría el chmod y se agregó el estado default de los permisos en sysfile.c junto con el comportamiento del sistema al tratar de realizar ciertas acciones cuando se tiene permissions de cierto valor. Por ejemplo se agregó lógica para no permitir que se continue el proceso si se esta intentando escribir en un archivo que tiene permisos de solo lectura. Se incluyó en este archivo también la funcionalidad de la llamada al sistema chmod.


Para definir la llamada se siguieron los pasos que ya se han observado en otras tareas:

1. Se definieron las llamadas en syscall.h
    #define SYS_chmod 24

2. en user.h se agregarón: 
    int chmod(const char*, int); //siendo la primera variable el archivo y la segunda el modo que se le asigna


3. Se definieron en syscall.c como:
    extern uint64 sys_chmod(void);
y
    [SYS_chmod]   sys_chmod

4. Finalmente se agregarón a usys.pl para ser llamadas:
    entry("chmod");

Finalmente se agregó la lógica al archivo de testeo para manejar múltiples posibles casos y probar asignando los distintos tipos con chmod, probando la funcionalidad de la llamada y la funcionalidad de la lógica agregada a los inodos, viendo que efectivamente se estuvieran siguiendo las reglas introducidas por los nuevos permisos.