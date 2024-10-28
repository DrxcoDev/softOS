# SoftOS

Is a simple operative system with a simple bootloader and kernel

# Requisites
  -  `GCC`
  -  `NASM`
  -  `WSL (IF YOU USE WINDOWS)`
  -  `QEMU`

# Start
1. `clone this repository`
2. Input: `./build.sh`

- You will can look a green text.

## Only Memory
1. `cd util`
2. Input: `./memory.sh`

# Files
¿How is launched the sesion?
SoftOS util a `build.sh` for launch it
- `./build.sh`:
  ``` bash
  mkdir bin
  nasm -f bin  bootloader/memory.asm -o bin/memory.bin
  nasm -f elf32 boot.asm -o boot.o
  gcc -m32 -c kernel.c -o kernel.o
  gcc -m32 -c ./src/print.c -o ./src/print.o
  ld -m elf_i386 -T link.ld -o ./bin/kernel.bin boot.o kernel.o ./src/print.o
  qemu-system-x86_64 -kernel ./bin/kernel.bin
  ```

