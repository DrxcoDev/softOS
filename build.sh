#!/bin/sh

# Crear los directorios bin y iso/boot/grub si no existen
mkdir -p bin
mkdir -p iso/boot/grub

# Compilar los archivos fuente del kernel con el flag -fno-stack-protector
gcc -ffreestanding -m32 -fno-stack-protector -c main.c -o ./bin/main.o
gcc -ffreestanding -m32 -fno-stack-protector -c ./src/print.c -o ./bin/print.o
gcc -ffreestanding -m32 -fno-stack-protector -c ./src/memory.c -o ./bin/memory.o
gcc -ffreestanding -m32 -fno-stack-protector -c ./src/shell.c -o ./bin/shell.o
gcc -ffreestanding -m32 -fno-stack-protector -c ./src/io.c -o ./bin/io.o
gcc -ffreestanding -m32 -fno-stack-protector -c ./src/keyboard.c -o ./bin/keyboard.o
gcc -ffreestanding -m32 -fno-stack-protector -c ./src/interrupts.c -o ./bin/interrupts.o

# Compilar el archivo de ensamblador
nasm -f elf ./src/idt_load.asm -o ./bin/idt_load.o

# Enlazar los archivos objeto en un binario de kernel
ld -m elf_i386 -T linker.ld -o ./bin/kernel.bin ./bin/main.o ./bin/print.o ./bin/memory.o ./bin/shell.o ./bin/io.o ./bin/keyboard.o ./bin/interrupts.o ./bin/idt_load.o

# Verificar si el enlace fue exitoso
if [ $? -eq 0 ]; then
    echo "Kernel compiled and linked successfully."
else
    echo "Linking failed."
    exit 1
fi

# Copiar el kernel y el archivo de configuraci�n de Grub
cp ./bin/kernel.bin iso/boot/kernel.bin
cp grub.cfg iso/boot/grub/grub.cfg

# Crear la imagen ISO de arranque con Grub
grub-mkrescue -o ./bin/os.iso iso

# Verificar si la creaci�n de la ISO fue exitosa
if [ $? -eq 0 ]; then
    echo "ISO image created successfully."
else
    echo "ISO creation failed."
    exit 1
fi

# Ejecutar el kernel en QEMU usando la imagen ISO
qemu-system-i386 -cdrom ./bin/os.iso