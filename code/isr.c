#include "io.h"
#include "isr.h"
#include "stdio.h"

void isr_handler(isr_registers *regs)
{  
  printf("Interrupt %d processed\n", regs->IntNo);
}

void irq_handler(isr_registers *regs)
{
  PIC_sendEOI(regs->IntNo);
  
  isr_p handler = interrupt_handlers[regs->IntNo];
  if(handler != 0) {
    handler(regs);
  }
}
