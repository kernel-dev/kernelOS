#ifndef KERN_EFI_MEM_H
#define KERN_EFI_MEM_H

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

/**
    The maximum address for an EFI
    memory descriptor.
 **/
#define MEMORY_UPPER_BOUNDARY     0xFFFFFFFFFFFFF000

/**
    Describes the structure of
    this kernel's custom memory map (UEFI MemMap).
 **/
typedef struct {
    UINTN                   MemoryMapSize;
    UINTN                   MMapKey;
    UINTN                   DescriptorSize;
    UINT32                  DescriptorVersion;
    EFI_MEMORY_DESCRIPTOR   *MemoryMap;
    BOOLEAN                 Empty;
} EFI_KERN_MEMORY_MAP;

/**
    Attempts to obtain the system memory map
    right before calling the kernel's EP.

    @param[in]  ImageHandle  The image handle.
    @param[in]  SystemTable  A pointer to the system table.

    @returns    A memory map contained in an
                EFI_KERN_MEMORY_MAP struct.
                The ".Empty" property will be
                TRUE if something went wrong,
                otherwise FALSE
 **/
EFI_KERN_MEMORY_MAP
EfiKernGetMemoryMap (
    IN EFI_HANDLE           ImageHandle, 
    IN EFI_SYSTEM_TABLE     *SystemTable);

#endif /* KernEfiMem.h */