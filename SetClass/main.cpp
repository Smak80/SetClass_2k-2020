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
	cout << s1;
	Set emptySet;
	cout << emptySet;
	els[0] = 1;
	els[1] = 12;
	els[2] = 113;
	els[3] = 145;
	els[4] = 45;
	Set s5(els);
	delete[] els;
	cout << s5;
	Set s2 = s1;
	Set s3 = emptySet;
	s3 = s2;
	Set s4 = s1 + s5;
	cout << s4;
	Set s6 = s1 * s5;
	cout << s6;
	Set s7 = s1 / s5;
	cout << s7;
	Set s8 = s1 - s5;
	cout << s8;
	try {
		cout << s8[1];
		cout << s8[100];
		cout << s8[0];
	}
	catch(const char* exception)
	{
		cout << exception << endl;
	}
	
	system("pause");
}