#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Util/KernRuntimeValues.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

UINT32                   ScreenRow   = 1;
UINT32                   ScreenCol   = 1;
KERN_FRAMEBUFFER         *FB         = NULL;
PSF_FONT_HDR             FontHdr;
PSF_FONT_HDR_EXTENDED    ExtFontHdr;
VOID                     *FontFile   = NULL;