#pragma once
#include <vector>

#define headersize 64

//default int size is 32bit.

class rarc
{
	struct headerbase {
		int magic;
		int size;
		int uk;
		int fidoffs;
		int fidsize;
		int fidsize2;
		int uk1;
		int uk2;
		int dinnumb;
		int dinoffs;
		int flenumb;
		int fleoffs;
		int strsize;
		int stroffs;
		int uk3;
		int padding;
	};
	struct dirnodebase
	{
		int folname;
		int strnaof;
		unsigned short namehash;
		unsigned short entnumb;
		int filoffs;
	};
	struct filentrybase
	{
		unsigned short fileid;
		unsigned short namehash;
		unsigned short type;
		unsigned short strnaof;
		unsigned int index;
		unsigned int size;
		unsigned int uk;
	};
	headerbase header;
	std::vector<dirnodebase> direnode;
	std::vector<filentrybase> fileentry;
	std::vector<char> string;
	std::vector<char> data;

protected:
	int c2i(char *a);
	unsigned short hashcal(char *name);

public:
	rarc(char *name);

	bool inputrarc(char *name);
	bool outputrarc(char *name);

	bool addfile(char *name, int dir);
	bool addfilenull(char *name, int dir);
	bool delfile(char *name, int dir);

	bool adddir(char *name, int dir);
	bool deldir(char *name, int dir);

	bool rename(char *name, int dir, char *newname);

};