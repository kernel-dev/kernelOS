#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/DebugLib.h>

VOID
ScreenClearTerminal (
    IN KERN_FRAMEBUFFER *FB
)
{
    //
    //  Fill the entirety of the framebuffer
    //  memory space with black pixels (0x0).
    //
    VolatileKernMemset32 (
        (UINT32 *)FB->FramebufferBase,
        0x0,
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
    //
    //  Iterate over every coordinate (X, Y),
    //  in accordance to the specified height-weight,
    //  and fill each corresponding memory space
    //  with the provided BGRA (32-bit) color.
    //
    for (UINT32 Vertical = Y; Vertical < (Y + Height); Vertical++)
    {
        for (UINT32 Horizontal = X; Horizontal < (X + Width); Horizontal++)
        {
            ScreenPutPixel (
                FB, 
                Horizontal, 
                Vertical,
                Color);
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
    UINT32 Address = (UINT32) (
        FB->FramebufferBase + (Y * FB->Pitch) + (FB->BPP * X)
    );

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
    *((volatile UINT32 *) (Address)) = Color;
}
