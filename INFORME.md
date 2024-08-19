1.- Descargue una máquina virtual para ejecutar el Oracle VM virtualbox con Kali linux (que utiliza Debian).

2.- Se hizo un Fork desde el repo de el profesor y después se clono el fork en la máquina virtual con linux.

3.- Utilice comandos recomendados por la página oficial de qemu para instalar qemu en debian => sudo apt-get install qemu-system-riscv64

4.- Confirme la instalación correcta de riscv corriendo sudo apt-get install gcc-riscv64-linux-gnu g++-riscv64-linux-gnu

5.- Luego agregue riscv al Path corriendo: export PATH=$HOME/riscv/bin:$PATH

6.- Descargue riscv GNU toolchain para linux siguiendo un tutorial.

7.- Finalmente entre a la carpeta clonada desde un terminal y corrí make qemu.

Pantallazos: 
