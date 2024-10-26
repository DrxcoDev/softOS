#include "./include/print.h"

void delay(int time)
{
    for (int i = 0; i < time * 1000000; i++)
    {
        __asm__("nop");  // No Operation, hace que la CPU no haga nada en cada iteración
    }
}

// void cpuid(int code, unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d)
// {
//     __asm__ volatile("cpuid"
//                      : "=a" (*a), "=b" (*b), "=c" (*c), "=d" (*d)
//                      : "a" (code));
// }

// void get_cpu_info(void)
// {
//     unsigned int eax, ebx, ecx, edx;
//     char cpu_vendor[13];  // El nombre del fabricante tiene 12 caracteres + '\0'

//     // Obtener el nombre del fabricante (cpuid con eax=0)
//     cpuid(0, &eax, &ebx, &ecx, &edx);

//     // Los registros ebx, edx, ecx contienen el nombre del fabricante en ese orden
//     *(unsigned int*)(cpu_vendor) = ebx;
//     *(unsigned int*)(cpu_vendor + 4) = edx;
//     *(unsigned int*)(cpu_vendor + 8) = ecx;
//     cpu_vendor[12] = '\0';  // Añadir el carácter nulo al final

//     // Mostrar el nombre del fabricante
//     print_msg("CPU Vendor: ", 0x02);  // Texto verde
//     print_msg(cpu_vendor, 0x02);
//     print_msg("\n", 0x02);

//     // Obtener la marca del procesador (cpuid con eax=0x80000002, 0x80000003, 0x80000004)
//     char cpu_brand[49];  // La marca completa ocupa 48 caracteres
//     cpuid(0x80000002, (unsigned int*)(cpu_brand), (unsigned int*)(cpu_brand + 4), (unsigned int*)(cpu_brand + 8), (unsigned int*)(cpu_brand + 12));
//     cpuid(0x80000003, (unsigned int*)(cpu_brand + 16), (unsigned int*)(cpu_brand + 20), (unsigned int*)(cpu_brand + 24), (unsigned int*)(cpu_brand + 28));
//     cpuid(0x80000004, (unsigned int*)(cpu_brand + 32), (unsigned int*)(cpu_brand + 36), (unsigned int*)(cpu_brand + 40), (unsigned int*)(cpu_brand + 44));
//     cpu_brand[48] = '\0';  // Añadir el carácter nulo al final

//     // Mostrar la marca del procesador
//     print_msg("CPU Brand: ", 0x02);  // Texto verde
//     print_msg(cpu_brand, 0x02);
//     print_msg("\n", 0x02);
// }


void kernel_main() {
    // Simple usage of print_msg() to print a string to the screen
    clear_screen();
    print_msg("kernel_main() has been called!\n", 0x02);
    delay(100); 
    // get_cpu_info();
    print_msg("Succes!\n", 0x02);
}
