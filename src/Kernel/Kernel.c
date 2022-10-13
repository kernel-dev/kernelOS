#include "Acpica/KernAcpi.h"
#include "Memory/KernMem.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

// Entry point for the kernel
EFI_STATUS
EFIAPI
KernelMain (
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    CHAR16                  *ExitData = NULL;
    EFI_STATUS              Status;
    EFI_KERN_MEMORY_MAP     MemoryMap;

    MemoryMap = EfiKernGetMemoryMap(ImageHandle, SystemTable);

    if (MemoryMap.Empty == TRUE)
        Print(L"KERN MEMORY MAP IS NULL!\n");

    else if (MemoryMap.MemoryMap != NULL)
    {
        UINT64 Region                           = 1;
        UINT64 MemoryBlockSize                  = 0;
        EFI_MEMORY_DESCRIPTOR *MemoryMapEntry   = MemoryMap.MemoryMap;
        EFI_MEMORY_DESCRIPTOR *MemoryMapEnd     = (EFI_MEMORY_DESCRIPTOR *) (
            (UINT8 *)(MemoryMap.MemoryMap) + (MemoryMap.MemoryMapSize)
        );

        Print(
            L"===> [EFIMEM]: First mem map entry = %llu | Second mem map entry = %llu\n",
            MemoryMapEntry,
            MemoryMapEnd);

        while (MemoryMapEntry < MemoryMapEnd)
        {
            if (
                MemoryMapEntry->PhysicalStart > 0 && 
                MemoryMapEntry->PhysicalStart < MEMORY_UPPER_BOUNDARY
            )
            {
                Print(L"===> [EFIMEM]: Region = %llu\n", Region);
                Print(L"===> [EFIMEM]: Number of pages = %llu\n", MemoryMapEntry->NumberOfPages);
                Print(L"===> [EFIMEM]: Physical start = 0x%x\n", MemoryMapEntry->PhysicalStart);
                Print(L"===> [EFIMEM]: Virtual start = 0x%x\n\n", MemoryMapEntry->VirtualStart);
                Print(L"===> [EFIMEM]: Type = %u\n", MemoryMapEntry->Type);
                Print(L"===> [EFIMEM]: Attribute = %llu\n\n", MemoryMapEntry->Attribute);

                MemoryBlockSize += MemoryMapEntry->NumberOfPages;
            }

            MemoryMapEntry = NEXT_MEMORY_DESCRIPTOR(MemoryMapEntry, MemoryMap.DescriptorSize);
            Region++;
        }

        Print(L"===> [EFIMEM]: Memory size = %llu\n", MemoryBlockSize * 4096);
        Print(L"===> [EFIMEM]: Size of memory map = %llu\n", MemoryMap.MemoryMapSize);
        Print(L"===> [EFIMEM]: Size of each region = %llu\n\n", MemoryMap.DescriptorSize);
    }

    EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER *Rsdp;
    EFI_ACPI_DESCRIPTION_HEADER                  *Rsdt;
    EFI_ACPI_DESCRIPTION_HEADER                  *Xsdt;
    EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE    *Fadt;
    ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE  *Dsdt;

    Status = EfiGetTables(&Rsdp, &Rsdt, &Xsdt, &Fadt, &Dsdt);

    if (Rsdp == NULL)
    {
        ExitData = L"MISSING RSDP";

        Print(L"===> [ACPI]: Could not find Rsdp...");

        SystemTable->BootServices->Exit(
            ImageHandle, 
            EFI_NOT_FOUND, 
            sizeof(ExitData), 
            ExitData);
    }

    else if (EFI_ERROR(Status))
    {
        ExitData = L"RSDP DISCOVERY FAILURE";

        Print(L"===> [ACPI]: Error occurred during discovery!\n");
    
        SystemTable->BootServices->Exit(
            ImageHandle, 
            EFIERR(Status), 
            sizeof(ExitData), 
            ExitData);
    }

    Print(
        L"===> [RSDP]: OemId = %c%c%c%c%c%c\n",
        Rsdp->OemId[0],
        Rsdp->OemId[1],
        Rsdp->OemId[2],
        Rsdp->OemId[3],
        Rsdp->OemId[4],
        Rsdp->OemId[5]);

    Print(
        L"===> [RSDP]: Signature Valid = %s\n\n", 
        Rsdp->Signature == EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER_SIGNATURE
            ? L"YES"
            : L"NO");

    Print(
        L"===> [XSDT]: OemId = %c%c%c%c%c%c\n",
        Xsdt->OemId[0],
        Xsdt->OemId[1],
        Xsdt->OemId[2],
        Xsdt->OemId[3],
        Xsdt->OemId[4],
        Xsdt->OemId[5]);

    Print(
        L"===> [XSDT]: Signature Valid = %s\n\n",
        Xsdt->Signature == EFI_ACPI_2_0_EXTENDED_SYSTEM_DESCRIPTION_TABLE_SIGNATURE
            ? L"YES"
            : L"NO");

    Print(
        L"===> [DSDT]: OemId = %c%c%c%c%c%c\n",
        Dsdt->Sdt.OemId[0],
        Dsdt->Sdt.OemId[1],
        Dsdt->Sdt.OemId[2],
        Dsdt->Sdt.OemId[3],
        Dsdt->Sdt.OemId[4],
        Dsdt->Sdt.OemId[5]);


    Print(
        L"===> [DSDT]: Dsdt Bytecode Count = %llu\n\n",
        Dsdt->BytecodeCount);

    return EFI_SUCCESS;
}