#pragma once

class bytest
{
	char* a;
	int count;
public:
	operator int();
	int operator+();
	bytest(char* b, int c);
	~bytest();
};

bytest::bytest(char* b, int c)
{
	count = c;
	a = new char[c];

	for (int i = 0; i < c; i++)
	{
		a[i] = b[i];
	}
}

bytest::operator int()
{
	int re = 0;
	for (int i = 0; i < 4; i++)
	{
		re += a[i] << (3 - i) * 8;
	}
	return re;
}

int bytest::operator+()
{
	return operator int();
}

bytest::~bytest()
{
	delete[] a;
}