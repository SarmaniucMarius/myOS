#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, UselessValue, ebx, edx, ecx, eax; // pushed by pusha
  uint32_t IntNo, ErrCode;
  uint32_t eip, cs, eflags, esp, ss; // pushed by the processor automatically
} isr_registers;

#endif
