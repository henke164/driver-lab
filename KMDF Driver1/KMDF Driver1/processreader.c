#include "processreader.h"
#include <stdio.h>
#include <Basetsd.h>

PEPROCESS Process;

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

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(__in PEPROCESS Process);

int InitializeProcess(int id)
{
	PsLookupProcessByProcessId(id, &Process);
	return Process ? 1 : 0;
}

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

UNICODE_STRING GetProcessMemoryStringValue(int address)
{
	UNICODE_STRING str;

	if (Process)
	{
		int readval;
		KeReadProcessMemory(Process, address, &readval, sizeof(__int32));
		RtlIntegerToUnicodeString(readval, 10, &str);
	}
	else
	{
		RtlInitUnicodeString(&str, L"Process not found");
	}

	return str;
}

int ProcessRunning()
{
	return Process ? 1 : 0;
}

int GetProcessBaseAddress()
{
	if (Process)
	{
		PVOID baseAddress = PsGetProcessSectionBaseAddress(Process);
		int addr = PtrToInt((INT_PTR)baseAddress);
		
		return addr;
	}
	return 0;
}