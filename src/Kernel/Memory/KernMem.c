#include "../../Common/Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID *
KernMemset (
    IN  VOID    *PTR,
    IN  INT64   CH,
    IN  INT64   Count
)
{
    unsigned char *Dest = PTR;

    while (Count--)
    {
        *Dest++ = (unsigned char) CH;
    }

    return PTR;
}