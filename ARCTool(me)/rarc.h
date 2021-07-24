#pragma once
#include <vector>
#include "castsize.h"
class rarc
{
private:
	char* filename;
	char headera[0x40] = { 0 };
	std::vector<char[0x10]> directoryna;
	std::vector<char[0x14]> fileentrya;
	std::vector<char> stringa;
	std::vector<char> filedata;
	int count[4] = { 0,0,0,0 };

protected:
	void sectionset();

	void directoryf();
	void fileentryf();
	void stringf();
	void filedataf();

	class casen
	{
	private:
		char* b;
	public:
		casen(const char* a, const int size);
		operator char* () { return b; };
	};

	void addfileS();
public:
	//base
	rarc();
	rarc(char* filename);

	//‘€ì
	int fopen();
	int fopen(char* filenam);
	int fwrite(char* filename);
	int view();
	int pkfile();
	int upkfile(char* filename);

	//Še€–Ú‚Ìo—Í
};