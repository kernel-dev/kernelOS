#ifndef KERNACPI_H
#define KERNACPI_H

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

/**
    Structure for a typical SDT (System Description Table)
    header, according to the ACPI 6.5 specification.
 **/
typedef struct {
    UINT32      Signature;
    UINT32      Length;
    UINT8       Revision;
    UINT8       Checksum;
    UINT8       OemId[6];
    UINT8       OemTableId[8];
    UINT8       OemRevision[4];
    UINT8       CreatorId[4];
    UINT8       CreatorRevision[4];
} SDT_HEADER;

/**
    Structure for the DSDT (Differentiated System Description Table),
    according to the ACPI 6.5 specification.
 **/
typedef struct {
    SDT_HEADER  Sdt;
    UINT64      BytecodeCount;
} ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE;

/**
    Attempts to locate the FADT by
    traversing the entires inside of XSDT.

    @param[in]      Xsdt            The XSDT.
    @param[out]     Fadt            The FADT to locate.

    @retval         EFI_SUCCESS     FADT was successfully found in the XSDT.
    @retval         EFI_ERROR       Something went wrong during the traversal.
    @retval         EFI_NOT_FOUND   The FADT could not be located. Maybe it's an ACPI 1.0 system?
                                    In which case, use the RSDT instead.
 **/
EFI_STATUS
EfiLocateFadtFromXsdt (
    IN  EFI_ACPI_DESCRIPTION_HEADER  *Xsdt,
    OUT EFI_ACPI_COMMON_HEADER       **Fadt);

/**
    Obtains all necessary tables... (using the RSDP initially)
    - RSDT (ACPI 1.0);
    - XSDT (ACPI 2.0+);
    - FADT;
    - DSDT

    @param[out]     Rsdp            The RSDP to locate.
    @param[out]     Rsdt            The RSDT to locate.
    @param[out]     Xsdt            The XSDT to locate.
    @param[out]     Fadt            The FADT to locate.

    @retval         EFI_SUCCESS     All necessary tables have been found
    @retval         EFI_ERROR       Something went wrong during the discovery process.
    @retval         EFI_NOT_FOUND   RSDP was not found. Something is definitely wrong.
 **/
EFI_STATUS
EfiGetTables (
    OUT EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER **Rsdp,
    OUT EFI_ACPI_DESCRIPTION_HEADER                  **Rsdt,
    OUT EFI_ACPI_DESCRIPTION_HEADER                  **Xsdt,
    OUT EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE    **Fadt,
    OUT ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE  **Dsdt);

#endif /* KernAcpi.h */