#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
// FIXME:   Plotting pixels to screen
//          does not work. Maybe the
//          FrameBufferBase is invalid?
//

VOID
ScreenClearTerminal (
    IN KERN_FRAMEBUFFER *FB
)
{
    //
    //  Fill the entirety of the framebuffer
    //  memory space with black pixels (0x0).
    //
    KernMemset (
        (VOID *) (UINT32 *) FB->FramebufferBase,
        0xFF,
        FB->FramebufferSize);
}

VOID
ScreenFillRectangle (
    IN KERN_FRAMEBUFFER *FB,
    IN UINT32           X,
    IN UINT32           Y,
    IN UINT32           Width,
    IN UINT32           Height,
    IN UINT32           Color
)
{
    UINT32 Horizontal = X;
    UINT32 Vertical = Y;

    //
    //  Iterate over every coordinate (X, Y),
    //  and in accordance to the specified height-weight,
    //  and fill each corresponding memory space
    //  with the provided BGRA (32-bit) color.
    //
    for (; Horizontal < (X + Width); Horizontal++)
    {
        for (; Vertical < (Y + Height); Vertical++)
        {
            ScreenPutPixel (FB, Horizontal, Vertical, Color);
        }
    }
}

VOID
ScreenPutPixel (
    IN KERN_FRAMEBUFFER *FB,
    IN UINT32           X,
    IN UINT32           Y,
    IN UINT32           Color
)
{
    //
    //  Locate the corresponding memory space
    //  based on the (X, Y) coordinates.
    //
    UINT32 Address = (UINT32) (FB->FramebufferBase + (Y * FB->Pitch + FB->BPP * X));

    //
    //  Cannot write pixel values to memory that
    //  is not a part of the framebuffer memory space.
    //
    if (Address > (FB->FramebufferBase + FB->FramebufferSize))
        return;

    //
    //  Replace contents of the memory block
    //  with the provided BGRA (32-bit) color.
    //
    *((UINT32 *) (Address)) = Color;
}
