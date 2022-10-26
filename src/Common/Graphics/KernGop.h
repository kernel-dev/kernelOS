#ifndef KERN_GOP_H
#define KERN_GOP_H

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

typedef struct {
    EFI_PHYSICAL_ADDRESS                FramebufferBase;
    EFI_PHYSICAL_ADDRESS                FramebufferSize;
    UINT64                              HorizontalRes;
    UINT64                              VerticalRes;
    UINT64                              PPS; // Pixels Per Scanline
    UINT64                              Pitch;
    UINT64                              Width;
    EFI_PIXEL_BITMASK                   PixelBitmask;
    UINT32                              CurrentMode;
} KERN_FRAMEBUFFER;

/**
    Locates the Graphics Output Protocol
    using its GUID.

    @param[in]      SystemTable     The system table.
    @param[out]     GOP             The graphics output protocol.

    @returns        EFI_SUCCESS     The GOP was successfully found.
                    EFI_NOT_FOUND   The GOP could not be found.
 **/
EFI_STATUS
KernLocateGop (
    IN  EFI_SYSTEM_TABLE                *SystemTable,
    OUT EFI_GRAPHICS_OUTPUT_PROTOCOL    *GOP);

/**
    Obtains the current video mode.

    @param[in]      GOP             The graphics output protocol.
    @param[out]     Info            The information about the currently set video mode.

    @returns        EFI_SUCCESS     The native video mode was found.
                    EFI_NOT_FOUND   The native video mode could not be found.
 **/
EFI_STATUS
KernGetVideoMode (
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *GOP,
    OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION    *Info,
    OUT UINTN                                   *SizeOfInfo);

/**
    Checks if the provided video mode is
    supported.

    @param[in]      VideoMode       The video mode to check against.
    @param[in]      SizeOfInfo      The size of the _GOP Info_ struct.
    @param[in]      GOP             The graphics output protocol.
    @param[in]      Info            The information about the currently set video mode.

    @returns        TRUE            The provided video mode is supported.
                    FALSE           The provided video mode is _NOT_ supported.
 **/
BOOLEAN
KernModeAvailable (
    IN UINT32                                   VideoMode,
    IN UINTN                                    *SizeOfInfo,
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL             *GOP,
    IN EFI_GRAPHICS_OUTPUT_MODE_INFORMATION     *Info);

#endif /* KernGop.h */