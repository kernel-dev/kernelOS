. /Users/kernel/Documents/edk2-oofer/edk2/BootloaderPkg/setup.sh

cd /Users/kernel/Documents/edk2-oofer/edk2/KernelOSPkg

rm -rf kernel.o 2> /dev/null
rm -rf hda-contents/kernel.bin* 2> /dev/null

# Compile
/usr/local/opt/llvm/bin/clang \
    --sysroot=/Users/kernel/Downloads/mingw64/lib/gcc/x86_64-w64-mingw32 \
    --target=x86_64-pc-windows-gnu \
    -Wl,-e,KernMain \
    -ffreestanding \
    -fuse-ld="/usr/local/bin/x86_64-w64-mingw32-ld" \
    -nostdlib \
    \
    -o kernel.o \
    src/Kernel/Kernel.c \
    src/Kernel/Memory/KernMem.c \
    src/Kernel/Graphics/KernGraphics.c \
    \
    -I/Users/kernel/Documents/edk2-oofer/edk2/MdePkg/Include/ \
    -I/Users/kernel/Documents/edk2-oofer/edk2/MdePkg/Include/X64 \
    -I/Users/kernel/Documents/edk2-oofer/edk2/KernelOSPkg/src/Common \
    -L/Users/kernel/Documents/edk2-oofer/edk2/MdePkg/Library/ \
    \
    -fshort-wchar \
    || exit 1 # Exit if something goes wrong

cp kernel.o hda-contents/kernel.bin 2> /dev/null

# Run the OVMF.fd inside of QEMU
qemu-system-x86_64 \
    -serial stdio \
    -bios bootloader/bios.bin \
    -drive file=fat:rw:hda-contents,format=raw,media=disk \
    -m 4096M \
    -s