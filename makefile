CFLAGS = -masm=intel -m32 -ffreestanding -fno-stack-protector -fno-pic -Wall -Wextra

all: clean bootloader kernel.bin bootdisk run

clean: 
	rm disk.img kernel.bin kernel.elf bootloader *.o &>/dev/null
	clear

bootloader:
	nasm -f bin -I boot/ boot/bootloader.asm -o bootloader

kernel.bin:	
	nasm -f elf32 kernel/kernelEntry.asm -o kernelEntry.o
	gcc $(CFLAGS) -I kernel/ -c kernel/*.c kernel/drivers/*.c
	ld -m elf_i386 -T link.ld *.o -o kernel.elf
	objcopy -O binary kernel.elf kernel.bin
	
bootdisk:
	dd if=/dev/zero of=disk.img bs=512 count=2880
	dd conv=notrunc if=bootloader of=disk.img bs=512 count=1 seek=0
	dd if=kernel.bin of=disk.img bs=512 count=20 seek=1

run:
	qemu-system-i386 -machine q35 -fda disk.img -gdb tcp::26000