#ifndef KERN_FONT_PARSER_H
#define KERN_FONT_PARSER_H

#include "./KernGraphics.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  PSF font (v1) magic number
//
#define PSF_FONT1_MAGIC  0x0436

/**
    Basic header representing a PSF font (v1) file.
 **/
typedef struct {
    UINT16  Magic;      // 2-byte magic number of the PSF font header.
    UINT8   Flags;      // 1-byte flag defining the properties of the character set.
    UINT8   Height;     // 1-byte value defining the height (size; bytes per row) of a character.
} PSF_FONT_HDR;

/**
    Extended header representing a PSF
    font file; mostly useful for internal
    usage to avoid redundancy.
 **/
typedef struct  {
    PSF_FONT_HDR    *Hdr;           // A pointer to the basic PSF font header.
    UINT32          NumOfGlyphs;    // The number of glyphs in this font file (bit 0 = 512, else 256).
    BOOLEAN         UnicodeTable;   // Whether or not this PSF file has a unicode table (bit 1 of Hdr->Flags).
    BOOLEAN         GlyphSeqs;      // Whether or not the encoding table contains character sequences (bit 2 of Hdr->Flags).
    UINT32          Width;          // Width of a glyph.
    UINT32          Height;         // Height (bytes per row) of a glyph.
} PSF_FONT_HDR_EXTENDED;

/**
    Parses the PSF file and "populates"
    the provided Hdr pointer with the
    corresponding data.

    Optionally also populates a PSF_FONT_HDR_EXTENDED
    pointer with the corresponding data.

    @param[in]  FontFile    The raw data of the font file.
    @param[out] Hdr         The PSF_FONT_HDR pointer.
    @param[out] ExtHdr      The PSF_FONT_HDR_EXTENDED pointer. (OPTIONAL)
    @param[in]  GetExtHdr   Whether or not to populate the ExtHdr. (OPTIONAL)
 **/
VOID
PSFInit (
    IN  VOID                    *FontFile, 
    OUT PSF_FONT_HDR            *Hdr,
    OUT PSF_FONT_HDR_EXTENDED   *ExtHdr     OPTIONAL,
    IN  BOOLEAN                 GetExtHdr
);

/**
    Initializes an array of glyphs (UINT32).

    Used for obtaining the corresponding glyph
    for an ASCII value of a character.

    @param[in]  FontFile    The raw data of the font file.
    @param[in]  ExtHdr      The PSF_FONT_HDR_EXTENDED pointer.
    @param[out] GlyphArray  The glyph array.
 **/
VOID
GlyphArrayInit (
    IN  VOID                    *FontFile,
    IN  PSF_FONT_HDR_EXTENDED   *ExtHdr,
    OUT UINT8                   *GlyphArray
);


#endif /* KernFontParser.h */