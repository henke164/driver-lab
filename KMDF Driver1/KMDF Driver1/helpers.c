#include "helpers.h"
#include <ntddk.h>
#include <stdio.h>
#include <stdlib.h>

int parseInt(PCHAR chars)
{
	int sum = 0;
	int len = strlen(chars);
	for (int x = 0; x < len; x++)
	{
		int n = chars[len - (x + 1)] - '0';
		sum = sum + powInt(n, x);
	}
	return sum;
}

void toString(char stNumber[10], int number)
{
	int nl = numberLength(number);

	if (nl > 10)
	{
		nl = 10;
	}

	for (int x = 0; x < nl; x++)
	{
		int no = getNumberAtPosition(number, x);
		stNumber[x] = no + '0';
	}
}

int getNumberAtPosition(int number, int position)
{
	int nl = numberLength(number);
	int loopCount = nl - position;
	int tal;
	for (int x = 0; x < loopCount; x++) {
		tal = (number % 10);
		number = number / 10;
	}
	return tal;
}

int numberLength(int number)
{
	number = abs(number);
	int length = 1;
	while ((number /= 10) >= 1)
		length++;
	return length;
}

int powInt(int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		x *= 10;
	}
	return x;
}