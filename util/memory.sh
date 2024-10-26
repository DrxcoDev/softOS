nasm -f bin  bootloader/memory.asm -o bin/memory.bin
echo "Succes"
qemu-system-x86_64 -drive format=raw,file=bin/memory.bin