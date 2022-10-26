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
    unsigned char *p = (unsigned char *) PTR;

    for (INT64 i = 0; i < Count; ++i, ++p) *p = (unsigned char) CH;

    return PTR;
}