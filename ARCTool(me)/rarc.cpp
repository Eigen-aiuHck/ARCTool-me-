#include "rarc.h"
#include <iostream>
#include <fstream>
#include <string>

#define int32 std::int32_t
#define uint32 std::uint32_t

int32 rarc::char2int(char *a)
{
	return *(int32*)a;
}

unsigned short rarc::hashcal(char *name)
{
	int32 i = 0;
	unsigned short hashval = 0;

	while (name[i] != '\0')
	{
		hashval *= 3;
		hashval += name[i];
		i++;
	}

	return hashval;
}

bool rarc::inputrarc(char *name)
{
	int32 seekval;

	std::ifstream read(name, std::ios::binary);
	if (!read) {
		std::cout << "Error: Can't open  file.\n";
		return 1;
	}
	
	read.seekg(std::ios_base::beg);
	read.read((char*)&header, headersize);
	
	seekval = header.dinoffs + 0x20;
	read.seekg(seekval, std::ios_base::beg);
	for (int32 i = 0; i < header.dinnumb; i++)
	{
		read.read((char*)direnode[i].folname, sizeof(int32));
		read.read((char*)direnode[i].strnaof, sizeof(int32));
		read.read((char*)direnode[i].namehash, sizeof(short));
		read.read((char*)direnode[i].entnumb, sizeof(short));
		read.read((char*)direnode[i].filoffs, sizeof(int32));
	}

	seekval = header.fleoffs + 0x20;
	read.seekg(seekval, std::ios_base::beg);
	for (int32 i = 0; i < header.flenumb; i++)
	{
		read.read((char*)fileentry[i].fileid, sizeof(short));
		read.read((char*)fileentry[i].namehash, sizeof(short));
		read.read((char*)fileentry[i].type, sizeof(short));
		read.read((char*)fileentry[i].strnaof, sizeof(short));
		read.read((char*)fileentry[i].index, sizeof(int32));
		read.read((char*)fileentry[i].size, sizeof(int32));
		read.read((char*)fileentry[i].uk, sizeof(int32));
	}

	seekval = header.stroffs + 0x20;
	read.seekg(seekval, std::ios_base::beg);
	read.read(&string[0], string.size());

	seekval = header.fidsize + 0x20;
	read.seekg(seekval, std::ios_base::beg);
	read.read(&data[0], data.size());

	return 0;
}

bool rarc::outputrarc(char *name)
{
	int32 seekval;

	std::ofstream write(name, std::ios::binary);
	if (!write) {
		std::cout << "Error: Can't open file.\n";
		return 1;
	}

	write.seekp(std::ios_base::beg);
	write.write((char*)&header, headersize);
	
	seekval = header.dinoffs + 0x20;
	write.seekp(seekval, std::ios_base::beg);
	for (int32 i = 0; i < header.dinnumb; i++)
	{
		write.write((char*)direnode[i].folname, sizeof(int32));
		write.write((char*)direnode[i].strnaof, sizeof(int32));
		write.write((char*)direnode[i].namehash, sizeof(short));
		write.write((char*)direnode[i].entnumb, sizeof(short));
		write.write((char*)direnode[i].filoffs, sizeof(int32));
	}

	seekval = header.fleoffs + 0x20;
	write.seekp(seekval, std::ios_base::beg);
	for (int32 i = 0; i < header.flenumb; i++)
	{
		write.write((char*)fileentry[i].fileid, sizeof(short));
		write.write((char*)fileentry[i].namehash, sizeof(short));
		write.write((char*)fileentry[i].type, sizeof(short));
		write.write((char*)fileentry[i].strnaof, sizeof(short));
		write.write((char*)fileentry[i].index, sizeof(int32));
		write.write((char*)fileentry[i].size, sizeof(int32));
		write.write((char*)fileentry[i].uk, sizeof(int32));
	}

	seekval = header.stroffs + 0x20;
	write.seekp(seekval, std::ios_base::beg);
	write.write(&string[0], string.size());

	seekval = header.fidsize + 0x20;
	write.seekp(seekval, std::ios_base::beg);
	write.write(&data[0], data.size());

	return 0;
}

bool rarc::addfile(char *name, int32 dir)
{
	char* namep;
	unsigned short stringp;
	uint32 namebeg = 0;
	int32 filesize;
	int32 fileover;
	uint32 datap;
	unsigned short fienp;


	std::ifstream addfile(name, std::ios::binary);
	if (!addfile)
	{
		std::cout << "Error: Can not input file!\n";
		return 1;
	}

	//file name add to rarc::string
	stringp = string.size();
	for(namebeg = std::strlen(name); name[namebeg] != '/'; namebeg--);
	for(uint32 i = 0; i < namebeg; i++)
	{
		string.push_back(name[i + namebeg]);
	}
	namep = &name[namebeg];

	//add entrys.
	header.flenumb += 1;

	direnode[dir].entnumb =+ 1;

	//add file data
	datap = data.size();

	addfile.seekg(0, std::ios::end);
	filesize = addfile.tellg();
	addfile.seekg(0, std::ios::beg);
	filesize = filesize - addfile.tellg();
	for(int32 i = 0; i < filesize; i++)  //I think the other code is a better.
	{
		char s;
		addfile.read(&s, sizeof(char));
		data.push_back(s);
	}
	
	fileover = filesize % 4;

	if(fileover != 0)for(int32 i = 0; i < fileover; i++)data.push_back((char)0x00); //Align the edges to 32 bits.

	//add file ent
	fienp = fileentry.size();
	fileentry.resize(fienp + 1);
	fileentry[fienp] = {fienp,hashcal(namep),0x0200,stringp,datap,(uint32)(data.size() + 1 - datap),0x00000000};
	
	return 0;
}

bool rarc::adddir(char *name, int32 dir)
{
	int32 nowdircount = 0;
	for(/* Declare the type */;direnode[nowdircount].folname <= dir;nowdircount++);
}