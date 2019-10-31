CC       = i686-elf-gcc
ASMCC    = nasm
EMULATOR = qemu-system-i386

CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra -Werror -pedantic
LINKFLAGS = -ffreestanding -nostdlib
EMUFLAGS = -kernel

DEPENDANCIES = $(wildcard *.h)
COBJS   = $(patsubst %.c, ../build/%.co, $(wildcard *.c))
ASMOBJS = $(patsubst %.S, ../build/%.ao, $(wildcard *.S))
CSRC    = $(wildcard *.c)
ASMSRC  = $(wildcard *.S)

default: run

../build/myos.bin: $(COBJS) $(ASMOBJS)
	$(CC) -T linker.ld -o $@ $(LINKFLAGS) $^ -lgcc

../build/%.co: %.c $(DEPENDANCIES)
	$(CC) -c $< -o $@ $(CFLAGS)

../build/%.ao: %.S
	$(ASMCC) -felf32 $< -o $@

run: ../build/myos.bin
	$(EMULATOR) $(EMUFLAGS) $<

clear:
	rm ../build/*
