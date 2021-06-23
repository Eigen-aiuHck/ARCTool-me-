#include <iostream>
#include <fstream>
#include "rarc.h"
#include "castsize.h"

//public

rarc::rarc(char* filename)
{
	if (filename == "")
	{
		std::cout << "Enter file name." << std::endl;
		std::cin >> rarc::filename;
	}
	else
	{
		rarc::filename = filename;
	}
	fopen(rarc::filename);
}

int rarc::fopen(char* filename)
{
	rarc::filename = filename;
	return fopen();
}

int rarc::fopen()
{
	std::fstream rarcfile(filename, std::ios::binary);

	if (!rarcfile)
	{
		std::cout << "Can't open file!!" << std::endl;
		return -1;
	}

	rarcfile.read(headera, sizeof(headera));

	if (headera[0] = !"RARC")
	{
		std::cout << "This is not RARC file!" << std::endl;
		return -2;
	}

	sectionset();

	for (int i = 0; i < count[0]; i++)rarcfile.read((char*)&directoryna[i], sizeof(directoryna[0]));

	for (int i = 0; i < count[0]; i++)rarcfile.read((char*)&fileentrya[i], sizeof(fileentrya[0]));

	for (int i = 0; i < count[0]; i++)rarcfile.read(&stringa[i], sizeof(char));

	for (int i = 0; i < count[0]; i++)rarcfile.read(&filedata[i], sizeof(char));

	rarcfile.close();

	return 0;
}

int rarc::fwrite(char* filename)
{
	std::fstream rarcfile(filename, std::ios::binary);

	if (!rarcfile)
	{
		std::cout << "Can't open file!!" << std::endl;
		return -1;
	}

	rarcfile.clear();

	for (int i = 0; i < count[0]; i++)rarcfile.write((char*)&directoryna[i], sizeof(directoryna[0]));

	for (int i = 0; i < count[1]; i++)rarcfile.write((char*)&fileentrya[i], sizeof(fileentrya[0]));

	for (int i = 0; i < count[2]; i++)rarcfile.write(&stringa[i], sizeof(char));

	for (int i = 0; i < count[3]; i++)rarcfile.write(&filedata[i], sizeof(char));

	int a = rarcfile.fail();
	rarcfile.close();

	return a;
}

int view()
{
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
	count[0] = (int)bytest(&headera[0x20], 4);
}

void rarc::fileentryf()
{
	count[1] = (int)bytest(&headera[0x28], 4);
}

void rarc::stringf()
{
	count[2] = (int)bytest(&headera[0x30], 4);
}

void rarc::filedataf()
{
	count[3] = (int)bytest(&headera[0x10], 4);
}