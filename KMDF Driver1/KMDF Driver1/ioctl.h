#pragma once

#include <ntddk.h>

void WriteToResponse(PDEVICE_OBJECT DeviceObject, PIRP irp, PCHAR data);

PCHAR ReadFromRequest(PIRP irp);

NTSTATUS IOCTL(PDEVICE_OBJECT DeviceObject, PIRP irp);

NTSTATUS UNSUPPORTED(PDEVICE_OBJECT DeviceObject, PIRP irp);