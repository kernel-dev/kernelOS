#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Graphics/KernText.h"
#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Util/KernString.h"
#include "../../Common/Util/KernRuntimeValues.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID
kprint ( IN CHAR8 *Str )
{
    ASSERT (Str != NULL);

    UINTN Len = _KernStrLen (Str);

    ASSERT (Len > 0);

    for (UINTN Index = 0; Index < Len; Index++)
    {
        if (Str[Index] == '\n')
        {
            ScreenCol = 1;
            ScreenRow++;
            continue;
        }

        PutChar (Str[Index]);
    }
}

VOID
PutChar ( IN CHAR8 Char )
{
    UINT8 *GlyphStart = ((UINT8 *)FontFile) + sizeof(PSF_FONT_HDR) + (Char * 16);
    UINT8 Glyph[16];
    
    for (UINTN N = 0; N < 16; N++)
        Glyph[N] = GlyphStart[N];

    for (UINTN DY = 0; DY < 16; DY++)
    {
        for (UINTN DX = 0; DX < 8; DX++)
        {
            UINT32 X = ScreenCol * ExtFontHdr.Width + DX;
            UINT32 Y = ScreenRow * ExtFontHdr.Height + DY;

            UINT32 BitIdx   = 7 - DX;
            UINT32 Bit      = (Glyph[DY] >> BitIdx) & 1;

            if (Bit == 1)
            {
                ScreenPutPixel (X, Y, 0xFFFFFFFF);
            }
        }
    }

    ScreenCol++;

    if (ScreenCol >= FB->HorizontalRes)
    {
        ScreenCol = 1;
        ScreenRow++;
    }
}