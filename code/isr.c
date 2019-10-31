#include "isr.h"
#include "stdio.h"

void isr_handler(isr_registers *regs)
{
  printf("DS: %h\n", regs->ds);
  printf("EDI: %d | ESI: %d | EBP: %h | UV: %h | EBX: %d | EDX: %d | ECX: %d | EAX: %d\n",
	 regs->edi, regs->esi, regs->ebp, regs->UselessValue, regs->ebx, regs->edx, regs->ecx, regs->eax);
  printf("INT_NO: %d | ERR_CODE: %d\n", regs->IntNo, regs->ErrCode);
  printf("EIP: %h | CS: %h | EFLAGS: %h | ESP: %d | SS: %d\n", regs->eip, regs->cs, regs->eflags, regs->esp, regs->ss);
  printf("Interrupt processed\n");
  //asm volatile("hlt");
}
