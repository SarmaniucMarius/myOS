#include "stdio.h"
#include "isr.h"
#include "timer.h"
#include "io.h"

uint32_t Tick = 0;

static void timer_callback(isr_registers *Regs)
{
  (void)(Regs);
  printf("Tick: %d\n", Tick++);
}

void init_timer(uint32_t Frequency)
{
  register_interrupt_handler(IRQ0, timer_callback);

  // The value we send to the PIT is the value to divide it's input clock
  // (1193180 Hz) by, to get our required frequency. Important to note is
  // that the divisor must be small enough to fit into 16-bits.
  uint16_t Divisor = 1193180 / Frequency;

  outb(0x43, 0x36);

  uint8_t Low = (Divisor >> 0) & 0xFF;
  uint8_t High = (Divisor >> 8) & 0xFF;

  outb(0x40, Low);
  outb(0x40, High);
}
