#ifndef ISR_H
#define ISR_H

#include <stdint.h>

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, UselessValue, ebx, edx, ecx, eax; // pushed by pusha
  uint32_t IntNo, ErrCode;
  uint32_t eip, cs, eflags, esp, ss; // pushed by the processor automatically
} isr_registers;

typedef void (*isr_p)(isr_registers*);
void register_interrupt_handler(uint8_t Entry, isr_p Handler);

isr_p interrupt_handlers[256];

#endif
