#include <ntifs.h>
#include <ntddk.h>
#include "processreader.h"
#include "helpers.h"
#include "communication.h"

#define IOCTL_INITIALIZE_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_GET_BASE_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_GET_MEMORY_VALUE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

void InitProcess(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	PCHAR value = ReadFromRequest(irp);
	int id = parseInt(value);
	int success = InitializeProcess(id);
	WriteINTToResponse(DeviceObject, irp, success);
}

UNICODE_STRING HandleBaseAddressRequest(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	if (ProcessRunning() == 0)
	{
		WritePCHARToResponse(DeviceObject, irp, L"Disabled");
	}
	else
	{
		int baseAddress = GetProcessBaseAddress();
		if (baseAddress > 0)
		{
			WriteINTToResponse(DeviceObject, irp, baseAddress);
		}
		else
		{
			WritePCHARToResponse(DeviceObject, irp, L"Failed to get baseaddress");
		}
	}
}

UNICODE_STRING HandleMemoryRequest(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	ULONGLONG address = 16395924;
	UNICODE_STRING memoryValue = GetProcessMemoryStringValue(address);
	WriteUNICODEToResponse(DeviceObject, irp, memoryValue);
}

NTSTATUS IOCTL(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	PIO_STACK_LOCATION io = IoGetCurrentIrpStackLocation(irp);
	ULONG ctlCode = io->Parameters.DeviceIoControl.IoControlCode;
	switch (ctlCode)
	{
		case IOCTL_INITIALIZE_PROCESS:
			InitProcess(DeviceObject, irp);
			break;
		case IOCTL_GET_BASE_ADDRESS:
			HandleBaseAddressRequest(DeviceObject, irp);
			break;
		case IOCTL_GET_MEMORY_VALUE:
			HandleMemoryRequest(DeviceObject, irp);
			break;
		default:
			break;
	}

	irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS Unsupported(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	DbgPrint("Unsupported routine called.\n");
	return STATUS_SUCCESS;
}
