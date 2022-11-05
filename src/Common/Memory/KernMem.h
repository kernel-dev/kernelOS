#ifndef KERN_MEM_H
#define KERN_MEM_H

#include "./KernEfiMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

/**
    Structure defining a physical memory page.
 **/
typedef struct {
    EFI_PHYSICAL_ADDRESS    Address;    // Beginning physical address of this page.
    UINT32                  Size;       // Size of this page.
    VOID                    *Buffer;    // The data this page holds.
    BOOLEAN                 Free;       // Whether or not this page is free to use.
} KERN_PHYSICAL_PAGE;

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
KernMemset32 (
    IN  VOID        *PTR,
    IN  INT32       Value,
    IN  UINT32      Count
);

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
KernMemset64 (
    IN  VOID        *PTR,
    IN  INT64       Value,
    IN  UINT64      Count
);

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    This implementation does a volatile write.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
VolatileKernMemset32 (
    IN  VOID        *PTR,
    IN  INT32       Value,
    IN  UINT32      Count
);

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    This implementation does a volatile write.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
VolatileKernMemset64 (
    IN  VOID        *PTR,
    IN  INT64       Value,
    IN  UINT64      Count
);

/**
    Copies the Source buffer to
    into the specified destination.

    @param[in]  Destination     The destination to copy the buffer into.
    @param[in]  Source          The source buffer (the data).
    @param[in]  Size            The size of the Source buffer (in bytes).
 **/
VOID
KernCopyMem (
    IN  VOID    *Destination,
    IN  VOID    *Source,
    IN  UINT64  Size
);


#endif /* KernMem.h */