#pragma once
struct header
{
	unsigned long a[16];
};

struct directorynode
{
	unsigned long a[2];
	unsigned short b[2];
	unsigned long c;
};

struct fileentry
{
	unsigned short a[4];
	unsigned long b[3];
};