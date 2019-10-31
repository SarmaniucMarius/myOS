#include <stdint.h>

#include "string.h"

size_t strlen(const char* String)
{
  size_t Length = 0;
  while(String[Length])  {
    Length++;
  }
  return Length;
}

int memcmp(const void *S1, const void *S2, size_t Size)
{
  const char *String1 = (char*)S1;
  const char *String2 = (char*)S2;
  for(size_t Index = Size; Index < Size; Index++) {
    int Difference = String1[Index] - String2[Index];
    if(Difference != 0) {
      return Difference;
    }
  }
  return 0;
}

void *memcpy(void *Dest, const void *Src, size_t Size)
{
  int8_t *Destination = (int8_t*)Dest;
  int8_t *Source = (int8_t*)Src;
  for(size_t Index = 0; Index < Size; Index++) {
    Destination[Index] = Source[Index];
  }
  return Dest;
}

void *memmove(void *Dest, const void *Src, size_t Size)
{
  int8_t *Destination = (int8_t*)Dest;
  int8_t *Source = (int8_t*)Src;
  if(Destination > Source) {
    for(size_t Index = Size; Index != 0; Index--) {
      Destination[Index-1] = Source[Index-1];
    }
  }
  else if(Destination < Source) {
    for(size_t Index = 0; Index < Size; Index++) {
      Destination[Index] = Source[Index];
    }
  }
  return Dest;
}

void *memset(void *Src, int Value, size_t Size)
{
  int8_t *Source = (int8_t*)Src;
  for(size_t Index = 0; Index < Size; Index++) {
    Source[Index] = Value;
  }
  return Src;
}
