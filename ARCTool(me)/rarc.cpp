#include <iostream>
#include <fstream>
#include "rarc.h"
#include "kata.h"
#include "castsize.h"

//public

rarc::rarc(char* filename)
{
	fopen(filename);
}

int rarc::fopen(char* filename)
{
	std::fstream rarcfile(filename, std::ios::binary);

	if (!rarcfile)
	{
		std::cout << "Can't open file!!" << std::endl;
		return -1;
	}

	rarcfile.read((char*)&headera, sizeof(header));

	if (headera.a[0][0] = !"RARC")
	{
		std::cout << "This is not RARC file!" << std::endl;
		return -2;
	}

	sectionset();

	for (int i = 0; i < count[0]; i++)rarcfile.read((char*)&directoryna[i], sizeof(directoryn));

	for (int i = 0; i < count[0]; i++)rarcfile.read((char*)&fileentrya[i], sizeof(fileentry));

	for (int i = 0; i < count[0]; i++)rarcfile.read(&stringa[i], sizeof(char));

	for (int i = 0; i < count[0]; i++)rarcfile.read(&filedata[i], sizeof(char));

	rarcfile.close();

	return 0;
}

//protected

void rarc::sectionset()
{
	directoryf();
	fileentryf();
	stringf();
	filedataf();
}

void rarc::directoryf()
{
	count[0] = (int)bytest((char*)&headera.a[8][0], 4);
}

void rarc::fileentryf()
{
	count[1] = (int)bytest((char*)&headera.a[10][0], 4);
}

void rarc::stringf()
{
	count[2] = (int)bytest((char*)&headera.a[12][0], 4);
}

void rarc::filedataf()
{
	count[3] = (int)bytest((char*)&headera.a[4][0], 4);
}