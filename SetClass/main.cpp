#include <iostream>

#include "set.h"
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
	set<int> s1(els);
	cout << s1;
	set<int> emptySet;
	cout << emptySet;
	els[0] = 1;
	els[1] = 12;
	els[2] = 113;
	els[3] = 145;
	els[4] = 45;
	set<int> s5(els);
	delete[] els;
	cout << s5;
	set<int> s2 = s1;
	set<int> s3 = emptySet;
	s3 = s2;
	set<int> s4 = s1 + s5;
	cout << s4;
	set<int> s6 = s1 * s5;
	cout << s6;
	set<int> s7 = s1 / s5;
	cout << s7;
	set<int> s8 = s1 - s5;
	cout << s8;
	try {
		cout << s8[1] << " ";
		cout << s8[100] << " ";
		cout << s8[0] << " ";
	}
	catch(const char* exception)
	{
		cout << exception << endl;
	}
	double* dels = new double[5];
	dels[0] = 1.1;
	dels[1] = 2.2;
	dels[2] = 13.1;
	dels[3] = 45.1;
	dels[4] = 45.1;
	set<double> ds1(dels);
	cout << ds1;
	system("pause");
}