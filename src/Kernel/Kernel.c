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
    IN ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE  **Dsdt,
    IN KERN_FRAMEBUFFER                             *Framebuffer)
{

    //
    //  Clear the screen.
    //
    ScreenClearTerminal (Framebuffer);

    //
    //  Fills the entire screen with
    //  bright yellow pixels.
    //
    ScreenFillRectangle (
        Framebuffer,
        0,
        0,
        Framebuffer->HorizontalRes * Framebuffer->PPS,
        Framebuffer->VerticalRes * Framebuffer->PPS,
        0xFFFFFF5F);

    //
    //  Should never reach here.
    //  Will be removed later.
    //
    while (TRUE) {};
}   