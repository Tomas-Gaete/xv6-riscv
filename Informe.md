
# Pasos para crear los llamados al sistema 

- Se crearon 2 system calls, sys_getppid y sys_getancestor para cumplir con los requisitos de la tarea.

- Primero se definieron las llamadas al sistema en syscall.h teniendo getppid como la llamada 22 y getancestor la llamada 23

- Se planteó la funcionalidad de estos llamados en el archivo sysproc.c

- Luego se llamó a estas funciones en syscall.c (ejemplo: extern uint64 sys_getppid(void);) y luego se relacionó esta función a la llamada del sistema en las syscalls de esta manera: static uint64 (*syscalls[])(void) {...[SYS_getppid] sys_getppid,...} (EJEMPLO)

- Luego en user.h se declararon las variables relacionadas a las sistem calls definidas int getppid(void) e int getancestor(int).
getancestor es int debido a como esta creada la función en sysproc.c que es void pero utiliza un argint para recibir el número que se utiliza para conseguir el respectivo ancestro.

- También se deben agregar entradas en usys.pl para estas funciones: entry("getppid"); (ejemplo)

# Pasos para crear el programa ejecutable en user

- Con las llamadas al sistema ya funcionales se creo el archivo yosoytupadre.c y se creo una función con argumentos para poder elegir el valor que utiliza getancestor usando un atoi() para recibir input en la terminal.

- Finalmente se modifica Makefile en el objeto de UPROGS para agregar a los archivos que se crean al archivo yosoytupadre.c permitiendo que este sea ejecutable.
Forma: 	"$U/_yosoytupadre\"