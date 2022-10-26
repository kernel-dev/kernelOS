#ifndef KERN_MEM_H
#define KERN_MEM_H

#include <Uefi.h>

#include <Library/UefiLib.h>

/**
    Representation of the virtual address
    space (page) a thread will see.
 **/
typedef struct {
    ///
    /// The beginning of the virtual page
    ///
    UINT64      Address;

    ///
    /// The size of this page
    ///
    UINT64      Size;

    ///
    /// The reference count of this page
    ///
    UINT32      RefCount;

    ///
    /// The value(s) stored inside of this page
    ///
    void        *Buffer;
    
    ///
    /// Whether or not this page is available for use.
    ///
    BOOLEAN     Available;
} KERNEL_VIRTUAL_MEMORY_PAGE;

/**
    Representation of the virtual-to-physical
    memory page map.
 **/
typedef struct {
    ///
    /// The pointer to the virtual page itself.
    ///
    KERNEL_VIRTUAL_MEMORY_PAGE  *VirtualPage;

    ///
    /// An array of physical addresses that make up
    /// the contiguous virtual page.
    ///
    UINT64                      *PhysicalAddress;
} KERNEL_PHYSICAL_MEMORY_PAGE;


#endif /* KernMem.h */