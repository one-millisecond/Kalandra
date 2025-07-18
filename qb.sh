clear
mkdir -p build
# assemble
nasm src/boot/boot.s -o build/bootloader.bin
nasm src/boot/bootmanager.s -o build/bootmanager.bin
nasm src/core/api/tty.s -o build/service_tty.bin
# image
dd if=/dev/zero of=os.img count=2880 bs=512
dd if=build/bootloader.bin of=os.img bs=512 conv=notrunc seek=0
dd if=build/bootmanager.bin of=os.img bs=512 conv=notrunc seek=1
# emulate
qemu-system-i386 -hda os.img