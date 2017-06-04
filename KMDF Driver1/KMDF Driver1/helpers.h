#pragma once
#include <ntddk.h>

void toString(char stNumber[], int number);

int parseInt(PCHAR chars);

int powInt(int x, int y);

int numberLength(int number);

int getNumberAtPosition(int number, int position);