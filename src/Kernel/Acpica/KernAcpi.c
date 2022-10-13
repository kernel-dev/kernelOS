#include "KernAcpi.h"

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <IndustryStandard/Acpi.h>
#include <Guid/Acpi.h>

EFI_STATUS
EfiLocateFadtFromXsdt (
    IN  EFI_ACPI_DESCRIPTION_HEADER  *Xsdt,
    OUT EFI_ACPI_COMMON_HEADER       **Fadt)
{   
    if (Xsdt == NULL)
        return EFIERR(EFI_INVALID_PARAMETER);

    EFI_ACPI_COMMON_HEADER *Table = NULL;

    UINT32  Signature    = EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE;
    UINT64  EntryPtr     = 0;
    UINTN   BasePtr      = (UINTN)(Xsdt + 1);
    UINTN   TablePtrSize = sizeof(Xsdt);
    UINTN   Entries      = (Xsdt->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER)) / TablePtrSize;

    for (UINTN Index = 0; Index < Entries; Index++)
    {
        EntryPtr = 0;

        CopyMem(
            &EntryPtr,
            (VOID *)(BasePtr + Index * TablePtrSize),
            TablePtrSize);

        Table = (EFI_ACPI_COMMON_HEADER *)((UINTN)(EntryPtr));

        if (Table != NULL && Table->Signature == Signature)
        {
            *Fadt = Table;
            return EFI_SUCCESS;
        }
    }

    return EFI_NOT_FOUND;
}

EFI_STATUS
EfiGetTables (
    OUT EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER **Rsdp,
    OUT EFI_ACPI_DESCRIPTION_HEADER                  **Rsdt,
    OUT EFI_ACPI_DESCRIPTION_HEADER                  **Xsdt,
    OUT EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE    **Fadt,
    OUT ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE  **Dsdt)
{
    *Rsdp = NULL;
    *Rsdt = NULL;
    *Xsdt = NULL;
    *Fadt = NULL;
    *Dsdt = NULL;

    EFI_STATUS Status;

    Status = EfiGetSystemConfigurationTable(&gEfiAcpi20TableGuid, (VOID **)Rsdp);

    if (EFI_ERROR(Status))
        return Status;

    if (*Rsdp == NULL)
        return EFI_NOT_FOUND;

    Print(L"\n===> [ACPI]: Found RSDP? = YES\n");

    *Xsdt = (EFI_ACPI_DESCRIPTION_HEADER *)(*Rsdp)->XsdtAddress;

    Print(
        L"===> [ACPI]: Found XSDT? = %s\n",
        *Xsdt == NULL
            ? L"NO"
            : L"YES");

    if (
        *Xsdt != NULL && 
        (*Xsdt)->Signature == EFI_ACPI_2_0_EXTENDED_SYSTEM_DESCRIPTION_TABLE_SIGNATURE
    )
    {
        Status = EfiLocateFadtFromXsdt(*Xsdt, (EFI_ACPI_COMMON_HEADER **)Fadt);

        if (EFI_ERROR(Status))
            Print(L"===> [ACPI]: UNKNOWN ERROR WHILE ATTEMPTING TO FIND FADT!\n");

        else if ((*Fadt)->Header.Signature == EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE)
            Print(L"===> [ACPI]: Found FADT? = YES\n");

        else if (*Fadt != NULL)
            Print(L"===> [ACPI]: TABLE FOUND, BUT IT'S NOT FADT!\n");

        else
            Print(L"===> [ACPI]: COULD NOT FIND FADT!\n");
    }

    if (*Fadt != NULL)
    {
        *Dsdt = (EFI_ACPI_COMMON_HEADER *)(UINTN)(*Fadt)->Dsdt;

        if (*Dsdt == NULL)
            Print(L"===> [ACPI]: COULD NOT FIND DSDT!\n");

        else
            Print(
                L"===> [ACPI]: Found DSDT? = %s\n\n",
                (*Dsdt)->Sdt.Signature == EFI_ACPI_2_0_DIFFERENTIATED_SYSTEM_DESCRIPTION_TABLE_SIGNATURE
                    ? L"YES"
                    : L"NO");

        (*Dsdt)->BytecodeCount = (*Dsdt)->Sdt.Length - sizeof((*Dsdt)->Sdt);
    }

    return EFI_SUCCESS;
}