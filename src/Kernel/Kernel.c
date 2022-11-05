#include "../Common/Acpi/KernEfiAcpi.h"
#include "../Common/Assert/KernAssert.h"
#include "../Common/Memory/KernEfiMem.h"
#include "../Common/Memory/KernMem.h"
#include "../Common/Graphics/KernGop.h"
#include "../Common/Graphics/KernGraphics.h"
#include "../Common/Graphics/KernFontParser.h"
#include "../Common/Util/KernRuntimeValues.h"

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
    IN KERN_FRAMEBUFFER                             *Framebuffer,
    IN VOID                                         *TerminalFont)
{
    FB = Framebuffer;
    FontFile = TerminalFont;

    //
    //  Clear the screen.
    //
    ScreenClearTerminal ();

    PSFInit (
        TerminalFont,
        &FontHdr,
        &ExtFontHdr,
        TRUE);

    kprint ("Hello, world!\n");


    //
    //  Should never reach here.
    //  Will be removed later.
    //
    while (TRUE) {};
}   