#pragma once

#include <ntddk.h>

NTSTATUS IOCTL(PDEVICE_OBJECT DeviceObject, PIRP irp);

NTSTATUS Unsupported(PDEVICE_OBJECT DeviceObject, PIRP irp);