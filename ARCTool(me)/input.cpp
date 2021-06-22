#include "input.h"
#include "kata.h"
#include "castsize.h"

input::~input()
{
	delete[] directoryna;
	delete[] fileentrya;
	delete filenamea;
	delete filedata;
}

void input::directoryf()
{
	count[0] = (int)bytest((char*)&heder.a[8][0], 4);
	directoryna = new directoryn[count[0]];
}

void input::fileentryf()
{
	count[1] = (int)bytest((char*)&heder.a[10][0], 4);
	fileentrya = new fileentry[count[1]];
}

void input::filenamef()
{
	count[2] = (int)bytest((char*)&heder.a[13][0], 4) + 0x20;
	filenamea = new char[count[2]];
}

void input::filedataf()
{
	count[3] = (int)bytest((char*)&heder.a[4][0], 4) + 0x20;
	filedata = new char[count[3]];
}