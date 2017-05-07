#include "processreader.h"
#include <stdio.h>

NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);

NTKERNELAPI NTSTATUS PsLookupProcessByProcessId(
	_In_ struct _DRIVER_OBJECT *DriverObject,
	_In_ PUNICODE_STRING RegistryPath
);

NTSTATUS KeReadProcessMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
	PEPROCESS TargetProcess = PsGetCurrentProcess();
	SIZE_T RSize;

	if (NT_SUCCESS(MmCopyVirtualMemory(Process, SourceAddress, TargetProcess, TargetAddress, Size, KernelMode, &RSize)))
	{
		return STATUS_SUCCESS;
	}
	return STATUS_ACCESS_DENIED;
}

PCHAR GetProcessMemoryStringValue()
{
	char arr[10] = "Hej";
	PCHAR c = (PCHAR)arr[10];
	return c;

	PEPROCESS Process;
	int readval;

	PsLookupProcessByProcessId(6448, &Process);

	if (Process)
	{
		KeReadProcessMemory(Process, 0x00F2342C, &readval, sizeof(__int32));
	}
	return "HEJ";
}