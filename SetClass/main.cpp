#include <iostream>

#include "Set.h"
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");
	int* els = new int[5];
	els[0] = 1;
	els[1] = 2;
	els[2] = 13;
	els[3] = 45;
	els[4] = 45;
	Set s1(els);
	Set emptySet;
	delete[] els;
	system("pause");
}