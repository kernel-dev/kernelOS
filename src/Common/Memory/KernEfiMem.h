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

#endif /* KernEfiMem.h */