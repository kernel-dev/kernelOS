#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Util/KernString.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

UINTN
_KernStrLen ( IN CHAR8 *String )
{
    ASSERT (String[0] != '\0');

    const CHAR8 *S;

    for (S = String; *S; ++S);

    return (S - String);
}