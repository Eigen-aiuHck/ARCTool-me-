#include <iostream>
#include <fstream>

int main(int stcount,const char* stringcl)
{
	std::fstream a(stringcl, std::ios::binary);

	a.write(stringcl,sizeof(&stringcl[0]));

	a.close();

	return 0;
}