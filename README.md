Informe tarea 2
=====================

# Este informe detalla como se logró implementar las funcionalidades detalladas en el enunciado de la tarea.

## Pasos iniciales:

### Comenzamos creando las llamadas del sistema para get boost, set boost, get priority y set priority

### Luego se agregaron priority y boost a:

proc.h =>int priority; int boost;   en la definicion de los struct proc (líneas 94 y 95)               

usys.pl => entry("setboost"); entry("getboost"); (líneas 43 y 44)

user.h =>  int setpriority(int priority); int getpriority(void); int setboost(int boost); int getboost(void); (como parte de los syscalls)

syscall.h => #define SYS_setpriority 24 #define SYS_getpriority 25 #define SYS_setboost 26 #define SYS_getboost 27 (líneas 25 -28)


syscall.c => extern uint64 sys_setpriority(void); extern uint64 sys_getpriority(void); extern uint64 sys_setboost(void); extern uint64 sys_getboost(void); y

[SYS_setpriority] sys_setpriority, [SYS_getpriority] sys_getpriority, [SYS_setboost] sys_setboost, [SYS_getboost] sys_getboost en sus áreas respectivas.


Se definieron las funciones en sysproc.c como tipo uint64

Cabe agregar que se realizaron algunos cambios pequeños en el proc.c para cambiar el comportamiento de los procesos.

### Después se desarrolló el código en t2_test que muestra en un ambiente controlado el comportamiento que tendrían los procesos con priority y boost implementados.

### IMPORTANTE: para correr este programa de pruebas se creo el archivo en la carpeta user y se agregó esta en el área respectiva del makefile dentro de uprogs (línea 144 del archivo)

### Finalmente se implementaron cambios en el scheduler de proc.c (desde línea 463) par que funcione con los boosts y priorities creados.