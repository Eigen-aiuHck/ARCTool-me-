#pragma once
#include "kata.h"
#include "castsize.h"
class rarc
{
private:
	header heder;
	directoryn* directoryna;
	fileentry* fileentrya;
	char* filenamea;
	char* filedata;
	int count[4];

public:
	void directoryf();
	void fileentryf();
	void filenamef();
	void filedataf();
	rarc();
	~rarc();
};