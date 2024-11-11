Informe Tarea 3
=======================================

Primero se creo y agregó el archivo t3_test al makefile para ser llamado para testear mprotect y munprotect una vez estos hayan sido creados.

Luego se observó que vm.c manejaba la lógica general del pagetable y se agraron al final de este archivo las definiciones específicas de las funcionalidades de mprotect(void *addr, int len) y munprotect(void *addr, int len).

Para utilizar las funciones definidas en vm.c se crearon 2 llamadas al sistema sys_mprotect y sys_munprotect.

Para definir las llamadas se siguieron los pasos que ya se han observado en otras tareas:

    1. Se definieron las llamadas en syscall.h
        #define SYS_mprotect 24
        #define SYS_munprotect 25

    2. en user.h se agregarón: 
        int mprotect(void *addr, int len);
        int munprotect(void *addr, int len);

    3. Se definieron en syscall.c como:
        extern uint64 sys_mprotect(void);
        extern uint64 sys_munprotect(void);
    y
        [SYS_mprotect] sys_mprotect,
        [SYS_munprotect] sys_munprotect,

    4. Finalmente se agregarón a usys.pl para ser llamadas:
        entry("mprotect");
        entry("munprotect");



Para utilizar mprotect y munprotect con sus respectivas llamadas se agregaron a sysproc.c ambos valores de esta forma:

    extern int mprotect(void *addr, int len);
    extern int munprotect(void *addr, int len);

Luego se utilizaron ambos valores dentro de las definiciones de sus respectivas syscalls

Finalmente se utilizó como base del archivo de testeo el ejemplo de test y se le agregó el testing the munprotect escribiendo en la memoria protegida despues de ocupar mprotect ocupando munprotect.