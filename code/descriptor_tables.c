#include "stdio.h"
#include "descriptor_tables.h"
#include "string.h"
#include "io.h"
#include "isr.h"

#define GDT_ENTRIES_COUNT 5
#define IDT_ENTRIES_COUNT 256

extern void load_gdt(gdt_descriptor*);
extern void load_idt(idt_descriptor*);

static void init_gdt();
static void set_gdt_entry(uint8_t Entry, uint32_t Base, uint32_t Limit, uint8_t Access, uint8_t Granularity);
static void init_idt();
static void set_idt_entry(uint8_t Entry, uint32_t Offset, uint16_t Selector, uint8_t Flags);
static void PIC_remap(int Offset1, int Offset2);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

static gdt_descriptor gdt;
static gdt_entry gdt_entries[GDT_ENTRIES_COUNT];
static idt_descriptor idt;
static idt_entry idt_entries[256];

void init_descriptor_tables()
{
  init_gdt();
  init_idt();
}

static void init_gdt()
{
  gdt.Size   = (sizeof(gdt_entry) * GDT_ENTRIES_COUNT) - 1;
  gdt.Offset = (uint32_t)gdt_entries;

  set_gdt_entry(0, 0, 0, 0, 0);
  set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

  load_gdt(&gdt);
}

static void set_gdt_entry(uint8_t Entry, uint32_t Base, uint32_t Limit, uint8_t Access, uint8_t Granularity)
{
  // Granularity is composed of Flags and Limit
  gdt_entries[Entry].LimitLow    = (Limit >>  0) & 0xFFFF;
  gdt_entries[Entry].Granularity = (Limit >> 16) & 0x0F; // set other bits of limit

  gdt_entries[Entry].BaseLow    = (Base >>  0) & 0xFFFF;
  gdt_entries[Entry].BaseMiddle = (Base >> 16) & 0xFF;
  gdt_entries[Entry].BaseHigh   = (Base >> 24) & 0xFF;

  gdt_entries[Entry].Access = Access;
  gdt_entries[Entry].Granularity |= Granularity & 0xF0; // set flags
}

static void init_idt()
{
  idt.Size   = (sizeof(idt_entry) * IDT_ENTRIES_COUNT) - 1;
  idt.Offset = (uint32_t)idt_entries;

  memset(idt_entries, 0, 256);

  set_idt_entry(0, (uint32_t)isr0, 0x08, 0x8E);
  set_idt_entry(1, (uint32_t)isr1, 0x08, 0x8E);
  set_idt_entry(2, (uint32_t)isr2, 0x08, 0x8E);
  set_idt_entry(3, (uint32_t)isr3, 0x08, 0x8E);
  set_idt_entry(4, (uint32_t)isr4, 0x08, 0x8E);
  set_idt_entry(5, (uint32_t)isr5, 0x08, 0x8E);
  set_idt_entry(6, (uint32_t)isr6, 0x08, 0x8E);
  set_idt_entry(7, (uint32_t)isr7, 0x08, 0x8E);
  set_idt_entry(8, (uint32_t)isr8, 0x08, 0x8E);
  set_idt_entry(9, (uint32_t)isr9, 0x08, 0x8E);
  set_idt_entry(10, (uint32_t)isr10, 0x08, 0x8E);
  set_idt_entry(11, (uint32_t)isr11, 0x08, 0x8E);
  set_idt_entry(12, (uint32_t)isr12, 0x08, 0x8E);
  set_idt_entry(13, (uint32_t)isr13, 0x08, 0x8E);
  set_idt_entry(14, (uint32_t)isr14, 0x08, 0x8E);
  set_idt_entry(15, (uint32_t)isr15, 0x08, 0x8E);
  set_idt_entry(16, (uint32_t)isr16, 0x08, 0x8E);
  set_idt_entry(17, (uint32_t)isr17, 0x08, 0x8E);
  set_idt_entry(18, (uint32_t)isr18, 0x08, 0x8E);
  set_idt_entry(19, (uint32_t)isr19, 0x08, 0x8E);
  set_idt_entry(20, (uint32_t)isr20, 0x08, 0x8E);
  set_idt_entry(21, (uint32_t)isr21, 0x08, 0x8E);
  set_idt_entry(22, (uint32_t)isr22, 0x08, 0x8E);
  set_idt_entry(23, (uint32_t)isr23, 0x08, 0x8E);
  set_idt_entry(24, (uint32_t)isr24, 0x08, 0x8E);
  set_idt_entry(25, (uint32_t)isr25, 0x08, 0x8E);
  set_idt_entry(26, (uint32_t)isr26, 0x08, 0x8E);
  set_idt_entry(27, (uint32_t)isr27, 0x08, 0x8E);
  set_idt_entry(28, (uint32_t)isr28, 0x08, 0x8E);
  set_idt_entry(29, (uint32_t)isr29, 0x08, 0x8E);
  set_idt_entry(30, (uint32_t)isr30, 0x08, 0x8E);
  set_idt_entry(31, (uint32_t)isr31, 0x08, 0x8E);

  PIC_remap(0x20, 0x28);
  
  memset(interrupt_handlers, 0, 256);
  
  set_idt_entry(32, (uint32_t)irq0, 0x08, 0x8E);
  set_idt_entry(33, (uint32_t)irq1, 0x08, 0x8E);
  set_idt_entry(34, (uint32_t)irq2, 0x08, 0x8E);
  set_idt_entry(35, (uint32_t)irq3, 0x08, 0x8E);
  set_idt_entry(36, (uint32_t)irq4, 0x08, 0x8E);
  set_idt_entry(37, (uint32_t)irq5, 0x08, 0x8E);
  set_idt_entry(38, (uint32_t)irq6, 0x08, 0x8E);
  set_idt_entry(39, (uint32_t)irq7, 0x08, 0x8E);
  set_idt_entry(40, (uint32_t)irq8, 0x08, 0x8E);
  set_idt_entry(41, (uint32_t)irq9, 0x08, 0x8E);
  set_idt_entry(42, (uint32_t)irq10, 0x08, 0x8E);
  set_idt_entry(43, (uint32_t)irq11, 0x08, 0x8E);
  set_idt_entry(44, (uint32_t)irq12, 0x08, 0x8E);
  set_idt_entry(45, (uint32_t)irq13, 0x08, 0x8E);
  set_idt_entry(46, (uint32_t)irq14, 0x08, 0x8E);
  set_idt_entry(47, (uint32_t)irq15, 0x08, 0x8E);

  load_idt(&idt);
  asm volatile("sti");
}

static void set_idt_entry(uint8_t Entry, uint32_t Offset, uint16_t Selector, uint8_t Flags)
{
  idt_entries[Entry].OffsetLow  = (Offset >>  0) & 0xFFFF;
  idt_entries[Entry].OffsetHigh = (Offset >> 16) & 0xFFFF;

  idt_entries[Entry].Selector = Selector;
  idt_entries[Entry].Zero     = 0;
  idt_entries[Entry].Flags    = Flags;
}

static void PIC_remap(int Offset1, int Offset2)
{
  unsigned char Mask1 = inb(PIC1_DATA);
  unsigned char Mask2 = inb(PIC2_DATA);

  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC1_DATA, Offset1);
  outb(PIC2_DATA, Offset2);
  outb(PIC1_DATA, 4);
  outb(PIC2_DATA, 2);

  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  outb(PIC1_DATA, Mask1);
  outb(PIC2_DATA, Mask2);
}

void register_interrupt_handler(uint8_t Entry, isr_p Handler)
{
  interrupt_handlers[Entry] = Handler;
}
