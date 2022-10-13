# Move to EDK2 directory
cd /Users/kernel/Documents/edk2-master/edk2/

# Source edksetup.sh to reconfigure config
. edksetup.sh

# Compile project
cd KernelOSPkg
build -a X64 -t XCODE5 -b RELEASE -p MdeModulePkg/MdeModulePkg.dsc || exit 1

# Copy EFI binary
cp ../Build/MdeModule/RELEASE_XCODE5/X64/KernelOSPkg/KernelOSPkg/OUTPUT/KernelOS.efi efi/KernelOS.efi
cp ../Build/MdeModule/RELEASE_XCODE5/X64/KernelOSPkg/KernelOSPkg/OUTPUT/KernelOS.efi hda-contents/KernelOS.efi

# Run the OS
qemu-system-x86_64 -pflash bootloader/bios.bin -hda fat:rw:hda-contents -net none