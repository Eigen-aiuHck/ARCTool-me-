#pragma once
#include <vector>
#include "castsize.h"
class rarc
{
private:
	char* filename;
	char headera[64] = {0};
	std::vector<char[16]> directoryna;
	std::vector<char[20]> fileentrya;
	std::vector<char> stringa;
	std::vector<char> filedata;
	int count[4] = { 0,0,0,0 };

protected:
	void sectionset();

	void directoryf();
	void fileentryf();
	void stringf();
	void filedataf();
public:
	//base
	rarc();
	rarc(char* filename);

	//‘€ì
	int fopen();
	int fopen(char* filenam);
	int fwrite(char* filename);
	int view();

	//Še€–Ú‚Ìo—Í
};