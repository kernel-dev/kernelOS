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

    while (Count > 0)
    {
        *Dest = (unsigned char) CH;

        Dest++;
        Count--;
    }

    return PTR;
}