#pragma once
#include <vector>
#include "kata.h"
#include "castsize.h"
class rarc
{
private:
	header headera = {0};
	std::vector<directoryn> directoryna;
	std::vector<fileentry> fileentrya;
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
	int fopen(char* filename);
	void fout(char* filename);
	int view();

	//Še€–Ú‚Ìo—Í
};