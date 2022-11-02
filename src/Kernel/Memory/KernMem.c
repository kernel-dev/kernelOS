#include "../../Common/Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID *
KernMemset32 (
    IN  VOID        *PTR,
    IN  INT32       Value,
    IN  UINT32      Count
)
{
    UINT32 *Dest = PTR;

    while (Count--)
    {
        *Dest++ = (UINT32) Value;
    }

    return PTR;
}

VOID *
KernMemset64 (
    IN  VOID        *PTR,
    IN  INT64       Value,
    IN  UINT64      Count
)
{
    UINT64 *Dest = PTR;

    while (Count--)
    {
        *Dest++ = (UINT64) Value;
    }

    return PTR;
}

VOID *
VolatileKernMemset32 (
    IN  VOID        *PTR,
    IN  INT32       Value,
    IN  UINT32      Count
)
{
    volatile UINT32 *Dest = PTR;

    while (Count--)
    {
        *Dest++ = (UINT32) Value;
    }

    return PTR;
}

VOID *
VolatileKernMemset64 (
    IN  VOID        *PTR,
    IN  INT64       Value,
    IN  UINT64      Count
)
{
    volatile UINT64 *Dest = PTR;

    while (Count--)
    {
        *Dest++ = (UINT64) Value;
    }

    return PTR;
}