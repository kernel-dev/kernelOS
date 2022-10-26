#include "../Common/Acpi/KernEfiAcpi.h"
#include "../Common/Memory/KernEfiMem.h"
#include "../Common/Graphics/KernGop.h"
#include "../Common/Graphics/KernGraphics.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

// Entry point for kernel
VOID
KernMain (
    IN EFI_RUNTIME_SERVICES                         *RT,
    IN EFI_KERN_MEMORY_MAP                          *MemoryMap,
    IN ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE  *Dsdt,
    IN KERN_FRAMEBUFFER                             *Framebuffer)
{
    ScreenClearTerminal (Framebuffer);
    ScreenFillRectangle (Framebuffer, 5, 5, 20, 20, 0xFF00);

    //
    //  Should never reach here.
    //  Will be removed later.
    //
    while (TRUE) {};
}   