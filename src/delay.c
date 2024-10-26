#include "../include/print.h"

void delay(int time)
{
    for (int i = 0; i < time * 1000000; i++)
    {
        __asm__("nop");  // No Operation, hace que la CPU no haga nada en cada iteración
    }
}