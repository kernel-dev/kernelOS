#ifndef KERN_RUNTIME_VALUES_H
#define KERN_RUNTIME_VALUES_H

#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Graphics/KernText.h"
#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  Screen row.
//
extern UINT32                   ScreenRow;

//
//  Screen column.
//
extern UINT32                   ScreenCol;

//
//  KERN_FRAMEBUFFER pointer.
//
extern KERN_FRAMEBUFFER         *FB;

//
//  PSF font header.
//
extern PSF_FONT_HDR             FontHdr;

//
//  Extended PSF font header.
//
extern PSF_FONT_HDR_EXTENDED    ExtFontHdr;

//
//  Contents of the current PSF file.
//
extern VOID                     *FontFile;

#endif /* KernRuntimeValues.h */