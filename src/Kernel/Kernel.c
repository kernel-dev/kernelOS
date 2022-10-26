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
    // ScreenPutPixel (&Framebuffer, 5, 5, 0xFF);
    // ScreenPutPixel (&Framebuffer, 15, 15, 0xFF00);
    // ScreenPutPixel (&Framebuffer, 25, 25, 0xFF0000);
    // ScreenPutPixel (&Framebuffer, 26, 26, 0xFF0000);
    // ScreenPutPixel (&Framebuffer, 27, 27, 0xFF0000);
    // ScreenPutPixel (&Framebuffer, 28, 28, 0xFF0000);
    // ScreenPutPixel (&Framebuffer, 29, 29, 0xFF0000);
    // ScreenClearTerminal(Framebuffer);
    ScreenClearTerminal (&Framebuffer);
    // ScreenFillRectangle (&Framebuffer, 5, 5, 20, 20, 0xFF00);

    // RT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);

    // Should never reach here.
    while (TRUE) {
        // ScreenClearTerminal (&Framebuffer);
    };
}   