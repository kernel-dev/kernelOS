# KernelOS

KernelOS, whilst still a WIP, is a toy OS I've built in my spare time for a school project. More precisely, I am doing my senior's paper/thesis on operating systems and kernels, and am providing this one as an example to detail how one may go about kernel/OS development.

## Goals

- [x] Custom bootloader to obtain basic information necessary, load the kernel image and call it with passed down arguments.
- [ ] Kernel-space memory management (pagers, vmem functions, etc.)
- [ ] Mutex locks for threads
- [ ] Basic Bash & C support
- [ ] PS/2 Keyboard support
- [ ] ACPICA implementation
- [ ] DSDT parser to expose the table in plaintext

## Credits / Resources

- [UEFI.org](https://uefi.org/specsandtesttools) - for providing exhaustive and detailed specifications of both UEFI and ACPI.
- [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page) - for providing me, and a plentiful of other users, with the common knowledge as an introduction for OS development.
- [Tianocore](https://github.com/tianocore/edk2) - for providing UEFI utilities and abstractions.
- [Mhaeuser](https://github.com/mhaeuser) — for providing this project with an amazing library for PE/COFF images (PeCoffLib2), which was used in the bootloader.