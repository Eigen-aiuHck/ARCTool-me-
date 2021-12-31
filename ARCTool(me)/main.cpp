#include <iostream>
#include "rarc.h"

#define int_32 std::int32_t
#define uint_32 std::int32_t

int main(int argc, char* argv[])
{
	if (argc == NULL)
	{
		std::printf("Command is rarc, if you want a option \"-hellp\" or \"-h\".");
		return NULL;
	}


	if (argv[1] == "-help" || argv[1] == "-h")
	{
		std::cout << "rarc \<command\>\n	-pac \"directory name\" \"compression file\"\n		compless file.\n	-upac \"package name\" \"decompression folder\"\n		decompress file.\n";
	}
	else if (argv[1] == "-pac")
	{

	}
	else
	{
		std::printf("Command is rarc, if you want a option \"-hellp\" or \"-h\".");
		return NULL;
	}

}