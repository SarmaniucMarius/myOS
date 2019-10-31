#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

#include <stdint.h>

void terminal_writestring(const char *String);
void terminal_putchar(char Char);
void terminal_initialize();
int terminal_writenumber(int32_t Value);
int terminal_writehex(uint32_t Value);

#endif
