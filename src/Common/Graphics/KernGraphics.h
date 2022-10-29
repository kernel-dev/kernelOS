#ifndef KERN_GRAPHICS_H
#define KERN_GRAPHICS_H

#include "KernGop.h"

#include <Uefi.h>
#include <Library/UefiLib.h>

/**
    Overwrites the entire framebuffer memory
    space with black pixels — [clears the screen].

    @param[in]  FB      The framebuffer.
 **/
VOID 
ScreenClearTerminal (
    IN KERN_FRAMEBUFFER *FB
);

/**
    Fills a rectangle (on the screen)
    beginning at the (X, Y) coordinates,
    and expanding according to the
    Height-Width values.

    @param[in]  FB      The KERN_FRAMEBUFFER pointer.
    @param[in]  X       The starting X coordinate.
    @param[in]  Y       The starting Y coordinate.
    @param[in]  Width   The length to expand across the X axis
    @param[in]  Height  The length to expand across the Y axis
    @param[in]  Color   The BGRA value of the wanted pixel.
 **/
VOID
ScreenFillRectangle (
    IN KERN_FRAMEBUFFER *FB,
    IN UINT32           X,
    IN UINT32           Y,
    IN UINT32           Width,
    IN UINT32           Height,
    IN UINT32           Color
);

/**
    Places a pixel at the specified
    FB memory space corresponding to the
    specified (X, Y) coordinates.

    @param[in]  FB      The KERN_FRAMEBUFFER pointer.
    @param[in]  X       The X coordinate.
    @param[in]  Y       The Y coordinate.
    @param[in]  Color   The BGRA value of the wanted pixel.
 **/
VOID
ScreenPutPixel (
    IN KERN_FRAMEBUFFER *FB,
    IN UINT32           X,
    IN UINT32           Y,
    IN UINT32           Color
);


#endif /* KernGraphics.h */