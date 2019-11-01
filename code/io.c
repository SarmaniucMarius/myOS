#include "io.h"

void outb(uint16_t Port, uint8_t Val)
{
  asm volatile("outb %0, %1" : : "a"(Val), "Nd"(Port));
}

uint8_t inb(uint16_t Port)
{
  uint8_t Result;
  asm volatile("inb %1, %0" : "=a" (Result) : "Nd" (Port));
  return Result;
}

void io_wait()
{
  asm volatile("outb %%al, $0x80" : : "a" (0));
}

void PIC_sendEOI(unsigned char irq)
{
  if(irq >= 40) {
    outb(PIC2_COMMAND, PIC_EOI);
  }
  outb(PIC1_COMMAND, PIC_EOI);
}
