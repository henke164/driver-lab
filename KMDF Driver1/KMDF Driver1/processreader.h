#pragma once
#include <ntddk.h>

int InitializeProcess(int id);

int ProcessRunning();

int GetProcessBaseAddress();

UNICODE_STRING GetProcessMemoryStringValue(int address);