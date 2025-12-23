CFLAGS = -masm=intel -m32 -ffreestanding -fno-stack-protector -fno-pic -Wall -Wextra
KFILES = kernel/*.c kernel/drivers/*/*.c kernel/lib/*.c kernel/interrupts/*.c

all: clean bootloader asm kernel.bin bootdisk run

clean: 
	rm disk.img kernel.bin kernel.elf bootloader *.o &>/dev/null
	clear

bootloader:
	nasm -f bin -I boot/ boot/bootloader.asm -o bootloader

asm:
	nasm -f elf32 kernel/kernelEntry.asm -o kernelEntry.o
	nasm -f elf32 kernel/drivers/io.asm -o io.o
	nasm -f elf32 kernel/interrupts/interrupts.asm -o asmInterrupts.o

kernel.bin:	
	gcc $(CFLAGS) -I kernel/ -c $(KFILES)
	ld -m elf_i386 -T link.ld *.o -o kernel.elf
	objcopy -O binary kernel.elf kernel.bin
	
bootdisk:
	dd if=/dev/zero of=disk.img bs=512 count=2880
	dd conv=notrunc if=bootloader of=disk.img bs=512 count=1 seek=0
	dd if=kernel.bin of=disk.img bs=512 count=20 seek=1

run:
	qemu-system-i386 -machine q35 -fda disk.img -gdb tcp::26000 