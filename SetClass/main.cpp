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
	//cout << s1;
	s1.showSet();
	set<int> emptySet;
	//cout << emptySet;
	emptySet.showSet();
	els[0] = 1;
	els[1] = 12;
	els[2] = 113;
	els[3] = 145;
	els[4] = 45;
	set<int> s5(els);
	delete[] els;
	//cout << s5;
	s5.showSet();
	set<int> s2 = s1;
	set<int> s3 = emptySet;
	s3 = s2;
	set<int> s4 = s1 + s5;
	//cout << s4;
	s4.showSet();
	set<int> s6 = s1 * s5;
	//cout << s6;
	s6.showSet();
	set<int> s7 = s1 / s5;
	//cout << s7;
	s7.showSet();
	set<int> s8 = s1 - s5;
	//cout << s8;
	s8.showSet();
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
	ds1.showSet();
	system("pause");
}