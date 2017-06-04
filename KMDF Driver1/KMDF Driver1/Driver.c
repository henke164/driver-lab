#include <ntifs.h>
#include <ntddk.h>
#include "ioctl.h"

DRIVER_INITIALIZE DriverEntry;
PDEVICE_OBJECT pDeviceObject;

VOID UnloadDriver(PDRIVER_OBJECT  DriverObject)
{
	UNICODE_STRING usDosDeviceName;

	RtlInitUnicodeString(&usDosDeviceName, L"\\DosDevices\\KMDFDriver1");
	IoDeleteSymbolicLink(&usDosDeviceName);

	IoDeleteDevice(DriverObject->DeviceObject);
}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	UNICODE_STRING dev, dos;
	DbgPrint("DriverEntry called.\n");

	RtlInitUnicodeString(&dev, L"\\Device\\KMDFDriver1");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\KMDFDriver1");

	IoCreateDevice(DriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	int uiIndex = 0;
	for (uiIndex = 0; uiIndex < IRP_MJ_MAXIMUM_FUNCTION; uiIndex++)
		DriverObject->MajorFunction[uiIndex] = Unsupported;

	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IOCTL;
	DriverObject->DriverUnload = UnloadDriver;
	
	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	DbgPrint("IOCTL Test driver loaded.\n");
	return STATUS_SUCCESS;
}