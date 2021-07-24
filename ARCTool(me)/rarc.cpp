#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>
#include <filesystem>
#include "rarc.h"
#include "castsize.h"

//public

rarc::rarc(char* filename)
{
	if (filename == "")
	{
		return;
	}

	if (std::strcmp(std::strrchr(filename,'.'),".arc") == 0)
	{
		std::cout << "Enter file name." << std::endl;
		std::cin >> rarc::filename;
		fopen();
	}
	else{
			//directory
		rarc::filename = filename;
		pkfile();
	}
}

int rarc::fopen(char* filename)
{
	rarc::filename = filename;
	return fopen();
}

int rarc::fopen()
{
	char fh[4];

	std::fstream rarcfile(filename, std::ios::binary);

	if (!rarcfile)
	{
		std::cout << "Can't open file!!" << std::endl;
		return -1;
	}

	rarcfile.read(headera, sizeof(headera));

	strcpy_s(fh,4,headera);
	if (strcmp(fh, "RARC") == 0)
	{
		std::cout << "This is not RARC file!" << std::endl;
		return -2;
	}

	sectionset();

	int* x;
	x = new int;

	*x = 0x20 + bytest(&headera[0x24], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[0]; i++)rarcfile.read((char*)&directoryna[i], sizeof(directoryna[0]));

	*x = 0x20 + bytest(&headera[0x2c], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[0]; i++)rarcfile.read((char*)&fileentrya[i], sizeof(fileentrya[0]));

	*x = 0x20 + bytest(&headera[0x34], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[0]; i++)rarcfile.read(&stringa[i], sizeof(char));

	*x = 0x20 + bytest(&headera[0x0c], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[0]; i++)rarcfile.read(&filedata[i], sizeof(char));

	rarcfile.close();

	return 0;
}

int rarc::fwrite(char* filename)
{
	std::ofstream rarcfile(filename, std::ios::binary);

	if (!rarcfile)
	{
		std::cout << "Can't open file!!" << std::endl;
		return -1;
	}

	rarcfile.clear();

	rarcfile.write(headera, sizeof(headera));
	
	int* x;
	x = new int;

	*x = 0x20 + bytest(&headera[0x24], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[0]; i++)rarcfile.write((char*)&directoryna[i], sizeof(directoryna[0]));

	*x = 0x20 + bytest(&headera[0x2c], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[1]; i++)rarcfile.write((char*)&fileentrya[i], sizeof(fileentrya[0]));

	*x = 0x20 + bytest(&headera[0x34], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[2]; i++)rarcfile.write(&stringa[i], sizeof(char));

	*x = 0x20 + bytest(&headera[0x0c], 4);
	rarcfile.seekp(*x, std::ios::beg);
	for (int i = 0; i < count[3]; i++)rarcfile.write(&filedata[i], sizeof(char));

	int a = rarcfile.fail();
	rarcfile.close();

	return a;
}

int rarc::pkfile()
{
	const int add = 1;

	const char* b;

	for (const auto& entry : std::filesystem::directory_iterator(filename))
	{
		const std::string a = entry.path().string();

		b = (char*)std::strrchr(a.c_str(), '/');

			//Directory or file check. And create file secsion.
		if (std::filesystem::is_directory(entry.path()))
		{	
			strcpy_s(&filename[0x20], 4, casen((const char*)&add, sizeof(4)));


		}
		else {
			strcpy_s(&filename[0x28], 4, casen((const char*)&add, sizeof(4)));
		}
		
		for (int i = 0; i < sizeof(b); i++)stringa.push_back(b[i]);
	}
}

int rarc::upkfile(char* filename)
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

	//4 code at under resemble.

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

rarc::casen::casen(const char* a, const int size)
{
	b = new char[size];

	for (int i = 0; i < size; i++)b[i] = a[size - 1 - i];
}


void rarc::addfileS()
{

}