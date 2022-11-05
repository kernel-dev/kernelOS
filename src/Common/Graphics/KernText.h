#ifndef KERN_TEXT_H
#define KERN_TEXT_H

#include "./KernGop.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

/**
    Prints a string to the screen.

    @param[in]  Str         The string to print.
 **/
VOID
kprint (
    IN CHAR8            *Str
);

/**
    Puts a character to the screen.

    @param[in]  Char        The character to "print".
 **/
VOID
PutChar (
    IN CHAR8            Char
);

#endif /* KernText.h */