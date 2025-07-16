clear
# assemble
nasm src/boot/boot.s -o build/bootloader.bin
# compile
wcc -0 -s -zl -zld -zls src/boot/boot.c
# link
wlink @link.lnk file boot.o name boot.bin
# move
cp boot.bin build/bootmanager.bin
# image
dd if=/dev/zero of=os.img count=2880 bs=512
dd if=build/bootloader.bin of=os.img bs=512 conv=notrunc seek=0
dd if=build/bootmanager.bin of=os.img bs=512 conv=notrunc seek=1
# emulate
rm -f *.bin *.err *.o
qemu-system-i386 -hda os.img