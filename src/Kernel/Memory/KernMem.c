#include "KernMem.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

EFI_KERN_MEMORY_MAP
EfiKernGetMemoryMap (
    IN  EFI_HANDLE              ImageHandle, 
    IN  EFI_SYSTEM_TABLE        *SystemTable)
{
    EFI_STATUS              Status;
    CHAR16                  *ExitData = NULL;

    EFI_KERN_MEMORY_MAP     EfiMemMap;
    UINTN                   MemoryMapSize = 0;
    UINTN                   MMapKey;
    UINTN                   DescriptorSize;
    UINT32                  DescriptorVersion;
    EFI_MEMORY_DESCRIPTOR   *MemoryMap;
    EFI_MEMORY_DESCRIPTOR   *MemoryMapEnd = NULL;
    EFI_PHYSICAL_ADDRESS    PagesAddr;

    Status = SystemTable->BootServices->AllocatePages(
        AllocateAnyPages,
        EfiLoaderData, 
        4,
        &PagesAddr);

    if (EFI_ERROR(Status))
    {
        ExitData = L"MEMORY PAGES ALLOC FAILURE";

        Print(
            L"===> [EFIMEM]: Memory pages allocation failed!!\nSTATUS = %llu\n", 
            EFIERR(Status));

        SystemTable->BootServices->Exit(
            ImageHandle, 
            Status, 
            sizeof(ExitData), 
            ExitData);
    }

    Status = SystemTable->BootServices->GetMemoryMap(
        &MemoryMapSize, 
        MemoryMap, 
        &MMapKey, 
        &DescriptorSize, 
        &DescriptorVersion);

    if (Status == EFI_BUFFER_TOO_SMALL)
    {
        Print(L"===> [EFIMEM]: Buffer was too small! New buffer size = %llu\n", MemoryMapSize);

        MemoryMap = (EFI_MEMORY_DESCRIPTOR *)AllocatePool(MemoryMapSize + (DescriptorSize * 2));
        UINTN NewMemoryMapSize = MemoryMapSize + (2 * DescriptorSize);

        Status = SystemTable->BootServices->GetMemoryMap(
            &NewMemoryMapSize,
            MemoryMap,
            &MMapKey,
            &DescriptorSize,
            &DescriptorVersion);

        if (EFI_ERROR(Status))
        {
            ExitData = L"MEMORY MAP FAILURE SECOND TRY";

            FreePool(MemoryMap);

            SystemTable->BootServices->Exit(
                ImageHandle, 
                EFIERR(Status), 
                sizeof(ExitData), 
                ExitData);
        }
    }

    else if (Status == EFI_INVALID_PARAMETER)
    {
        Print(L"===> [EFIMEM]: Invalid parameter!\n");
    }

    else if (EFI_ERROR(Status))
    {
        ExitData = L"MEMORY MAP FAILURE";

        Print(
            L"===> [EFIMEM]: Obtaining memory map for loader failed!!\nSTATUS = %llu\n", 
            EFIERR(Status));

        SystemTable->BootServices->Exit(
            ImageHandle, 
            Status, 
            sizeof(ExitData),
            ExitData);
    }

    if (MemoryMap == NULL)
        EfiMemMap = (EFI_KERN_MEMORY_MAP){ .Empty = TRUE }; // Memory map not found; the function should never reach this condition.

    else
        EfiMemMap = (EFI_KERN_MEMORY_MAP){
            .MemoryMapSize      = MemoryMapSize,
            .MMapKey            = MMapKey,
            .DescriptorSize     = DescriptorSize,
            .DescriptorVersion  = DescriptorVersion,
            .MemoryMap          = MemoryMap,
            .Empty              = FALSE
        };

    return EfiMemMap;
}