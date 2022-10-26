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
    KernMemset (
        (VOID *) (UINT32 *) FB->FramebufferBase,
        0x00,
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
    UINT32 Address = (FB->FramebufferBase + (Y * FB->Pitch + FB->Width * X));

    //
    //  Cannot write pixel values to memory that
    //  is not a part of the framebuffer space.
    //
    if (Address > (FB->FramebufferBase + FB->FramebufferSize))
        return;

    *((UINT32 *) (Address)) = Color;
}
