#ifndef KERN_GRAPHICS_H
#define KERN_GRAPHICS_H

#include "KernGop.h"

#include <Uefi.h>
#include <Library/UefiLib.h>

VOID 
ScreenClearTerminal (
    IN KERN_FRAMEBUFFER **FB
);

VOID
ScreenFillRectangle (
    IN KERN_FRAMEBUFFER **FB,
    IN UINT32           X,
    IN UINT32           Y,
    IN UINT32           Width,
    IN UINT32           Height,
    IN UINT32           Color
);

VOID
ScreenPutPixel (
    IN KERN_FRAMEBUFFER **FB,
    IN UINT32           X,
    IN UINT32           Y,
    IN UINT32           Color
);


#endif /* KernGraphics.h */