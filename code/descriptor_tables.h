#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

#include <stdint.h>

struct gdt_descriptor_struct {
  uint16_t Size;
  uint32_t Offset;
} __attribute__((packed));
typedef struct gdt_descriptor_struct gdt_descriptor;

struct gdt_entry_struct {
  uint16_t LimitLow;
  uint16_t BaseLow;
  uint8_t  BaseMiddle;
  uint8_t  Access;
  uint8_t  Granularity;
  uint8_t  BaseHigh;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry;

struct idt_descriptor_struct {
  uint16_t Size;
  uint32_t Offset;
} __attribute__((packed));
typedef struct idt_descriptor_struct idt_descriptor;

struct idt_entry_struct {
  uint16_t OffsetLow;
  uint16_t Selector;
  uint8_t  Zero;
  uint8_t  Flags;
  uint16_t OffsetHigh;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry;

void init_descriptor_tables();

#endif
