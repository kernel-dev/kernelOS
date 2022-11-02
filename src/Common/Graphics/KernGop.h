#ifndef KERN_GOP_H
#define KERN_GOP_H

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

/**
    A struct describing the passed down
    framebuffer to the kernel's EP.
 **/
typedef struct {
    EFI_PHYSICAL_ADDRESS                FramebufferBase;    // The base address of the framebuffer.
    EFI_PHYSICAL_ADDRESS                FramebufferSize;    // The total size of the framebuffer memory space (max address = FramebufferBase + FramebufferSize).
    UINT32                              HorizontalRes;      // The horizontal resolution of this mode.
    UINT32                              VerticalRes;        // The vertical resolution of this mode.
    UINT32                              PPS;                // Pixels Per Scanline.
    UINT64                              BPP;                // The "bytes per pixel" value.
    UINT64                              Pitch;              // Density of the pixel (BPP * PPS).
    EFI_PIXEL_BITMASK                   PixelBitmask;       // The pixel definition of the physical framebuffer.
    UINT32                              CurrentMode;        // The index of the wanted mode.
} KERN_FRAMEBUFFER;

/**
    Locates the Graphics Output Protocol
    using its GUID.

    @param[in]      SystemTable     The system table.
    @param[out]     GOP             The graphics output protocol.

    @retval         EFI_SUCCESS     The GOP was successfully found.
    @retval         EFI_NOT_FOUND   The GOP could not be found.
 **/
EFI_STATUS
KernLocateGop (
    IN  EFI_SYSTEM_TABLE                *SystemTable,
    OUT EFI_GRAPHICS_OUTPUT_PROTOCOL    *GOP);

/**
    Obtains the current video mode.

    @param[in]      GOP             The graphics output protocol.
    @param[out]     Info            The information about the currently set video mode.

    @retval         EFI_SUCCESS     The native video mode was found.
    @retval         EFI_NOT_FOUND   The native video mode could not be found.
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

    @retval         TRUE            The provided video mode is supported.
    @retval         FALSE           The provided video mode is _NOT_ supported.
 **/
BOOLEAN
KernModeAvailable (
    IN UINT32                                   VideoMode,
    IN UINTN                                    *SizeOfInfo,
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL             *GOP,
    IN EFI_GRAPHICS_OUTPUT_MODE_INFORMATION     *Info);

#endif /* KernGop.h */