#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"

#include <Uefi.h>
#include <Library/UefiLib.h>

//
// FIXME:   Plotting pixels to screen
//          from (0, 0) to (H, V) yields
//          an exception.
//
VOID
ScreenClearTerminal (
    IN KERN_FRAMEBUFFER **FB
)
{
    ScreenFillRectangle (
        FB,
        0, 
        0,
        (*FB)->HorizontalRes,
        (*FB)->VerticalRes,
        0x0);
}

VOID
ScreenFillRectangle (
    IN KERN_FRAMEBUFFER **FB,
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
    IN KERN_FRAMEBUFFER **FB,
    IN UINT32           X,
    IN UINT32           Y,
    IN UINT32           Color
)
{
    UINT32 Address = ((*FB)->FramebufferBase + (Y * (*FB)->Pitch + (*FB)->Width * X));

    *((UINT32 *) (Address)) = Color;
}
