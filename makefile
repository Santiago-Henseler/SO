all: bootloader bootdisk run

clean: 
	rm disk.img bootloader 
	clear

bootloader:
	nasm -f bin boot/bootloader.asm -o bootloader

bootdisk:
	dd if=/dev/zero of=disk.img bs=512 count=2880
	dd conv=notrunc if=bootloader of=disk.img bs=512 count=1 seek=0

run:
	qemu-system-i386 -machine q35 -fda disk.img -gdb tcp::26000