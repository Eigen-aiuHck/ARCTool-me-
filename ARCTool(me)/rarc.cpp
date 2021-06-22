#include "rarc.h"
#include "kata.h"
#include "castsize.h"

rarc::~rarc()
{
	delete[] directoryna;
	delete[] fileentrya;
	delete filenamea;
	delete filedata;
}

void rarc::directoryf()
{
	count[0] = (int)bytest((char*)&heder.a[8][0], 4);
	directoryna = new directoryn[count[0]];
}

void rarc::fileentryf()
{
	count[1] = (int)bytest((char*)&heder.a[10][0], 4);
	fileentrya = new fileentry[count[1]];
}

void rarc::filenamef()
{
	count[2] = (int)bytest((char*)&heder.a[13][0], 4) + 0x20;
	filenamea = new char[count[2]];
}

void rarc::filedataf()
{
	count[3] = (int)bytest((char*)&heder.a[4][0], 4) + 0x20;
	filedata = new char[count[3]];
}