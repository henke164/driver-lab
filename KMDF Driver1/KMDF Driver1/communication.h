#pragma once

#include <ntddk.h>

void WriteINTToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, int number);

BOOLEAN IsStringTerminated(PCHAR pString, int uiLength, int *pdwStringLength);

void WriteUNICODEToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, UNICODE_STRING data);

void WritePCHARToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, PCHAR data);

PCHAR ReadFromRequest(PIRP irp);