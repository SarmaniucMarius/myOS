#include "stdio.h"
#include "isr.h"
#include "io.h"

void keyboard_callback(isr_registers *regs)
{
  (void)(regs);
  printf("darova\n");
  inb(0x60);
}

void init_keyboard()
{
  register_interrupt_handler(IRQ1, keyboard_callback);
  
  while(inb(0x64) & 0x1) {
    inb(0x60);
  }

  outb(0x64, 0xAE);
  outb(0x64, 0x20);
  uint8_t state = (inb(0x60) | 1) & ~0x10;
  outb(0x64, 0x60);
  outb(0x60, state);
  outb(0x60, 0xF4);
}
