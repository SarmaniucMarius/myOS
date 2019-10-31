#include <stddef.h>

#include "descriptor_tables.h"
#include "vga.h"
#include "stdio.h"
#include "string.h"

void kernel_main()
{
  init_descriptor_tables();
  terminal_initialize();
}
