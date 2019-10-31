	[GLOBAL load_gdt]

load_gdt:
	mov eax, [esp + 4]
	lgdt [eax]

	; Reload data segment register
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	; Reload code segment register 
	jmp 0x08:.reload_CS
.reload_CS:
	ret

	[GLOBAL load_idt]

load_idt:
	mov eax, [esp + 4]
	lidt [eax]
	ret
