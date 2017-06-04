#include <ntddk.h>
#include "communication.h"
#include "helpers.h"

void WriteINTToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, int number)
{
	char p[20] = "";
	toString(&p, number);
	PCHAR outputBuffer = NULL;

	if (irp->MdlAddress)
	{
		outputBuffer = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
	}

	if (outputBuffer)
	{
		RtlCopyMemory(outputBuffer, p, sizeof(p));
	}

}
void WritePCHARToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, PCHAR data)
{
	PCHAR outputBuffer = NULL;

	if (irp->MdlAddress)
	{
		outputBuffer = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
	}

	if (outputBuffer)
	{
		RtlCopyMemory(outputBuffer, data, sizeof(data));
	}
}

void WriteUNICODEToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, UNICODE_STRING data)
{
	PCHAR outputBuffer = NULL;
	
	if (irp->MdlAddress)
	{
		outputBuffer = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
	}

	if (outputBuffer)
	{
		RtlCopyMemory(outputBuffer, data.Buffer, data.Length);
	}
}

PCHAR ReadFromRequest(PIRP irp)
{
	PCHAR pInputBuffer = irp->AssociatedIrp.SystemBuffer;

	if (pInputBuffer)
	{
		return pInputBuffer;
	}

	return "No message";
}

BOOLEAN IsStringTerminated(PCHAR pString, int uiLength, int *pdwStringLength)
{
	BOOLEAN bStringIsTerminated = FALSE;
	int uiIndex = 0;

	*pdwStringLength = 0;

	while (uiIndex < uiLength && bStringIsTerminated == FALSE)
	{
		if (pString[uiIndex] == '\0')
		{
			*pdwStringLength = uiIndex + 1;
			bStringIsTerminated = TRUE;
		}
		else
		{
			uiIndex++;
		}
	}

	return bStringIsTerminated;
}
