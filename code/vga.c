#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "string.h"

enum vga_color {
  BLACK         = 0,
  BLUE          = 1,
  GREEN         = 2,
  CYAN          = 3,
  RED           = 4,
  MAGENTA       = 5,
  BROWN         = 6,
  LIGHT_GREY    = 7,
  DARK_GREY     = 8,
  LIGHT_BLUE    = 9,
  LIGHT_GREEN   = 10,
  LIGHT_CYAN    = 11,
  LIGHT_RED     = 12,
  LIGHT_MAGENTA = 13,
  LIGHT_BROWN   = 14,
  WHITE         = 15
};

static inline uint8_t vga_entry_color(enum vga_color Foreground, enum vga_color Background)
{
  return (uint8_t)Foreground | ((uint8_t)Background) << 4;
}

static inline uint16_t vga_entry(unsigned char Char, uint8_t Color)
{
  return (uint16_t)Char | ((uint16_t)Color) << 8;
}

typedef struct
{
  size_t Row;
  size_t Column;
  uint8_t Color;
  uint16_t *Buffer; 
} vga_terminal;

vga_terminal Terminal;

void terminal_initialize()
{
  Terminal.Row = 0;
  Terminal.Column = 0;
  Terminal.Color = vga_entry_color(LIGHT_GREY, BLACK);
  Terminal.Buffer = (uint16_t*) 0xB8000;
  for(size_t Y = 0; Y < VGA_HEIGHT; Y++) {
    for(size_t X = 0; X < VGA_WIDTH; X++) {
      const size_t Index = Y * VGA_WIDTH + X;
      Terminal.Buffer[Index] = vga_entry(' ', Terminal.Color);
    }
  }
}

static void terminal_putentryat(char Char, uint8_t Color, size_t X, size_t Y)
{
  const size_t Index = Y * VGA_WIDTH + X;
  Terminal.Buffer[Index] = vga_entry(Char, Color);
}

static void terminal_scroll()
{
  Terminal.Row = VGA_HEIGHT - 1;
  for(size_t Width = 0; Width < VGA_WIDTH; Width++){
    for(size_t Height = 1; Height < VGA_HEIGHT; Height++) {
      const size_t CurrentRow  = Width + Height * VGA_WIDTH;
      const size_t PreviousRow = CurrentRow - VGA_WIDTH;
      Terminal.Buffer[PreviousRow] = Terminal.Buffer[CurrentRow];
    }
  }
  for(size_t Width = 0; Width < VGA_WIDTH; Width++) {
    const size_t Index = Width + Terminal.Row * VGA_WIDTH;
    Terminal.Buffer[Index] = ' ';
  }
}

// Will break for stuff like \r, \t
void terminal_putchar(char Char)
{
  if(Char != '\n') {
    terminal_putentryat(Char, Terminal.Color, Terminal.Column, Terminal.Row);
    if(++Terminal.Column == VGA_WIDTH) {
      Terminal.Column = 0;
      Terminal.Row++;
    }
  }
  else {
    Terminal.Column = 0;
    Terminal.Row++;
  }

  if(Terminal.Row == VGA_HEIGHT) {
    terminal_scroll();
  }
}

static void terminal_write(const char *Data, size_t Size)
{
  for(size_t Index = 0; Index < Size; Index++) {
    terminal_putchar(Data[Index]);
  }
}

void terminal_writestring(const char *String)
{
  terminal_write(String, strlen(String));
}

static int terminal_writeuint(uint32_t Value)
{
  char Buf[10]; // max number of digits is 10
  size_t Counter = 0;
  while(Value != 0) {
    int LastDigit = Value % 10;
    Buf[Counter++] = '0' + LastDigit;
    Value /= 10;
  }

  char Number[11]; // one more element for '\0'
  size_t Index = 0;
  while(Counter != 0) {
    Number[Index++] = Buf[--Counter];
  }
  Number[Index] = '\0';
  terminal_writestring(Number);

  return Index;
}

static int terminal_writeint(int32_t Value)
{
  uint32_t PositiveValue = (~Value) + 1;
  
  char Buf[11]; // man number of digits is 10 and +1 element for - symbol
  Buf[0] = '-';
  size_t Counter = 1;
  while(PositiveValue != 0) {
    int LastDigit = PositiveValue % 10;
    Buf[Counter++] = '0' + LastDigit;
    PositiveValue /= 10;
  }
  Counter--;
  
  char Number[12]; // one more element for '\0'
  Number[0] = Buf[0];
  size_t Index = 1;
  while(Counter != 0) {
    Number[Index++] = Buf[Counter--];
  }
  Number[Index] = '\0';
  terminal_writestring(Number);

  return Index;
}

int terminal_writenumber(int32_t Value)
{
  size_t Length = 1;
  if(Value == 0) {
    terminal_putchar('0');
    return Length;
  } else if (Value > 0) {
    Length = terminal_writeuint((uint32_t) Value);
    return Length;
  } else {
    Length = terminal_writeint(Value);
    return Length;
  }
}

int terminal_writehex(uint32_t Value)
{
  char Buf[8];  // any 32 bit value can be represented with 8 hex digits
  if(Value == 0) {
    Buf[0] = '0';
    Buf[1] = 'x';
    Buf[2] = '0';
    Buf[3] = '\0';
    terminal_writestring(Buf);
    return 3;
  }
  
  size_t Counter = 0;
  int NrOfShifts = 0;
  while(Value != 0) {
    int Digit = Value & 0xF;
    switch(Digit) {
    case 10:
      Buf[Counter++] = 'A';
      break;
    case 11:
      Buf[Counter++] = 'B';
      break;
    case 12:
      Buf[Counter++] = 'C';
      break;
    case 13:
      Buf[Counter++] = 'D';
      break;
    case 14:
      Buf[Counter++] = 'E';
      break;
    case 15:
      Buf[Counter++] = 'F';
      break;
    default:
      Buf[Counter++] = '0' + Digit;
      break;
    }
    NrOfShifts += 4;
    Value = Value >> NrOfShifts;
  }

  char Number[11];
  Number[0] = '0';
  Number[1] = 'x';
  size_t Index = 2;
  while(Counter != 0) {
    Number[Index++] = Buf[--Counter];
  }
  Number[Index] = '\0';
  terminal_writestring(Number);

  return Index;
}
