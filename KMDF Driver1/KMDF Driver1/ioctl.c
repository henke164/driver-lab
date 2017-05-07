#include <ntifs.h>
#include <ntddk.h>
#include "processreader.h"

void WriteToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, PCHAR data)
{
	size_t dataSize = strlen(data);
	PCHAR outputBuffer = NULL;

	if (irp->MdlAddress)
	{
		outputBuffer = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
	}

	if (outputBuffer)
	{
		RtlCopyMemory(outputBuffer, data, dataSize);
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

NTSTATUS IOCTL(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	PCHAR value = GetProcessMemoryStringValue();
	//PCHAR returnData = ReadFromRequest(irp);

	WriteToResponse(DeviceObject, irp, value);

	irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS UNSUPPORTED(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	DbgPrint("Unsupported routine called.\n");
	return STATUS_SUCCESS;
}
