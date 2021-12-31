#pragma once
#include <vector>

#define headersize 64
#define int32 std::int32_t
#define uint32 std::uint32_t

//default int32 size is 32bit.

class rarc
{
	struct headerbase {
		int32 magic;
		int32 size;
		int32 uk;
		int32 fidoffs;
		int32 fidsize;
		int32 fidsize2;
		int32 uk1;
		int32 uk2;
		int32 dinnumb;
		int32 dinoffs;
		int32 flenumb;
		int32 fleoffs;
		int32 strsize;
		int32 stroffs;
		int32 uk3;
		int32 padding;
	};
	struct dirnodebase
	{
		int32 folname;
		int32 strnaof;
		unsigned short namehash;
		unsigned short entnumb;
		int32 filoffs;
	};
	struct filentrybase
	{
		unsigned short fileid;
		unsigned short namehash;
		unsigned short type;
		unsigned short strnaof;
		uint32 index;
		uint32 size;
		uint32 uk;
	};
	headerbase header;
	std::vector<dirnodebase> direnode;
	std::vector<filentrybase> fileentry;
	std::vector<char> string;
	std::vector<char> data;

protected:
	int32 char2int(char* a);
	unsigned short hashcal(char* name);

public:

	bool inputrarc(char *name);
	bool outputrarc(char *name);

	bool addfile(char *name, int32 dir);
	// bool addfilenull(char *name, int32 dir);
	// bool delfile(char *name, int32 dir);

	bool adddir(char *name, int32 dir);
	// bool deldir(char *name, int32 dir);

	bool inportdir(char *dir);
	bool export_dir(char *name);
	// bool rename(char *name, int32 dir, char *newname);

};