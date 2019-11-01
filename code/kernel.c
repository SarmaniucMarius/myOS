#include <stddef.h>

#include "descriptor_tables.h"
#include "vga.h"
#include "stdio.h"
#include "string.h"
#include "timer.h"
#include "keyboard.h"

void kernel_main()
{
  terminal_initialize();
  init_descriptor_tables();

  init_timer(50);
  for(;;) {
    asm volatile("hlt");
  }
}
