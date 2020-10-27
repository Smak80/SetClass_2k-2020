#pragma once
#include <ostream>

class Set
{
	struct elem
	{
		int value;
		elem* next = nullptr;
	};
	//�������� ���������
	int cardinality = 0;
	//������ ��������� (��������� �� ������ �������)
	elem* first_el = nullptr;
	//��������� �� ��������� ������� ������
	elem* last_el = nullptr;
	//��������������� ������� ��� ����������� ������ ���������
	void copy_set(const Set& other);
	//����� �������� ��������� ���������
	void clear_set();
public:
	//������ ����������� �� ��������� ��������� ��� �������� ������� ���������
	Set(){}
	//����������� � ���������� ��� �������� ��������� �� ������ ��������� �������
	explicit Set(int* elems);
	//����������� �����������
	Set(const Set& other);
	//����������
	~Set();
	//������� ��� ���������� ������ �������� � ���������
	bool add(int elem);
	//����� �������� �������� �� ���������
	bool remove(int elem);
	//����� �������� ������� �������� �� ���������
	bool is_in_set(int elem) const;

	//�������� ������������
	Set& operator=(const Set& other);
	//�������� ����������� ��������
	Set operator+(const Set& other) const;
	//�������� ����������� ��������
	Set operator*(const Set& other) const;
	//�������� ��������
	Set operator/(const Set& other) const;
	//�������������� �������� �������
	Set operator-(const Set& other) const;
	//�������� ��������������
	int& operator[](int index);

	//����� ��������� ���������
	friend std::ostream& operator<<(std::ostream& out, const Set& set);
};
