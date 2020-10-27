#include "Set.h"

#include <corecrt_malloc.h>

/**
 * ��������������� ������� ��� ����������� ��������� ���������
 */
void Set::copy_set(const Set& other)
{
	//�������� ����� ������ �� ��������� other
	elem* curr = other.first_el;
	while (curr)
	{
		auto* newel = new elem;
		newel->value = curr->value;
		if (last_el) last_el->next = newel;
		else first_el = newel;
		last_el = newel;
		curr = curr->next;
	}
}

/**
 * �������� ������ ��������� ���������
 */
void Set::clear_set()
{
	elem* curr = first_el;
	while (curr)
	{
		elem* del = curr;
		curr = curr->next;
		delete del;
	}
	first_el = last_el = nullptr;
	cardinality = 0;
}

/**
 * ����������� � ���������� ������� ��������� �� ������� ���������
 * @param els - �������� �������, ����������� �� ���������
 */
Set::Set(int* els)
{
	//���������, ��� ������ �� ������
	if (!els) return;
	//��������� ������ ������� ��� ��� ������ � ������ ���������� �� ������ 0�� ��������
	auto sz = _msize(els) / sizeof *els;
	//��������� ������ ������� �� ������� �� ���������
	for (size_t i = 0; i<sz; i++)
	{
		add(els[i]);
	}
}

/**
 * ����������� �����������
 */
Set::Set(const Set& other) : cardinality(other.cardinality)
{
	copy_set(other);
}

/**
 * ����������. ���������� ��� �������� ���������� ������ �� ������
 */
Set::~Set()
{
	clear_set();
}

/**
 * ����� ���������� �������� � ���������
 * @param el - ����������� �������
 * @return ���������� true, ���� ������� �������� � false, ���� ������� ��� ��� �� ���������
 */
bool Set::add(int el)
{
	//�������� �� ������� ����������� ��������� �� ���������
	if (!is_in_set(el))
	{
		//���� ������� ������������ �� ���������, �������� ������ ��� �������� � ������
		elem* newel = new elem;
		//��������� ��������
		newel->value = el;
		//���� ��������� ���� ������, �� ����� ������� ���������� ������ � ���������
		if (!first_el) first_el = last_el = newel;
		else {
			//���� �� ��������� ���� ��������, �� ��������� ����� ������� ����� ����������
			last_el->next = newel;
			last_el = newel;
		}
		//����������� �������� ���������
		cardinality++;
		return true;
	}
	return false;
}

/**
 * ����� �������� �������� �� ���������
 * @param el - ��������� �������
 * @return - ���������� true, ���� ������� ��� ������, � ��������� ������ - false;
 */
bool Set::remove(int el)
{
	//���� ������ ��� (��������� ������), ����� �������
	if (!first_el) return false;
	if (first_el->value == el)
	{
		//���� ����� ������� ������ �������
		elem* del = first_el;
		first_el = first_el->next;
		delete del;
		//���� ������ ������� ���������, �� ���������� � ���������
		if (!first_el) last_el = nullptr;
		cardinality--;
		return true;
	}
	//������������� ��������� �� ������ �������
	elem* curr = first_el;
	//���� �� ������ �� �������������� �������� ��������� ��� ��������, �������� ��������
	//����� ���������� ��������
	while (curr->next && curr->next->value != el)
	{
		//��������� � ���������� ��������
		curr = curr->next;
	}
	//���� ���� ��������� �������, ������ ���� ����������� ������, ��� ��������
	//���������� �������� ���� �������
	if (curr->next)
	{
		//������� �������, ��������� �� �������
		elem* del = curr->next;
		curr->next = curr->next->next;
		delete del;
		//���� ����� ��������� ������� ��� �������� ���� ����, ������
		//��� ������ ��������� �������: ��������� ��������������� ���������.
		if (!curr->next) last_el = curr;
		cardinality--;
		return true;
	}
	return false;
}

/**
 * ����� �������� ������� �������� �� ���������
 * @param el ����������� �� ������� �� ��������� �������
 * @return ���������� true, ���� ������� ������������ �� ��������� � false, � ��������� ������
 */
bool Set::is_in_set(int el) const
{
	//������������� ��������� �� ������ �������
	elem* curr = first_el;
	//���� �� ������ �� ������� ������ ��������� ���������
	while (curr)
	{
		//���� ������ �������, ���������� true
		if (curr->value == el) return true;
		//����� ��������� � ���������� ��������
		curr = curr->next;
	}
	return false;
}

/**
 * �������� ������������
 */
Set& Set::operator=(const Set& other)
{
	//�������� �� ����������������
	if (this == &other) return *this;
	clear_set();
	cardinality = other.cardinality;
	copy_set(other);
	return *this;
}

/**
 * ����������� ��������
 * @param other - ������ ���������, � ������� ����� ���������� �����������
 * @return - ����� ������������ ���������
 */
Set Set::operator+(const Set& other) const
{
	Set res = *this;
	elem* curr = other.first_el;
	while (curr)
	{
		res.add(curr->value);
		curr = curr->next;
	}
	return res;
}

/**
 * �������� ����������� ��������
 * @param other ������ ��������� ��� ������ �����������
 * @return ����������� ��������
 */
Set Set::operator*(const Set& other) const
{
	Set res;
	elem* curr = (cardinality > other.cardinality) ? first_el : other.first_el;
	const Set& ts = (cardinality > other.cardinality) ? other : *this;
	while (curr)
	{
		if (ts.is_in_set(curr->value)) res.add(curr->value);
		curr = curr->next;
	}
	return res;
}

/**
 * �������� ��� ���������� �������� ��������
 * @param other - ���������� ��������
 * @return �������� ��������, �� ������������ � ���������� ���������
 */
Set Set::operator/(const Set& other) const
{
	Set res(*this);
	elem* curr = first_el;
	while (curr)
	{
		if (other.is_in_set(curr->value)) res.remove(curr->value);
		curr = curr->next;
	}
	return res;
}

Set Set::operator-(const Set& other) const
{
	return (*this + other) / (*this * other);
}

/**
 * �������� �������������� (����- � ��������������)
 * 
 */
int& Set::operator[](int index)
{
	if (index < 0 || index >= cardinality)
		throw "Out of range";
	int i = 0;
	elem* curr = first_el;
	while (curr)
	{
		if (i == index) return curr->value;
		curr = curr->next;
		i++;
	}	
}

/**
 * �������� ������ �� ����� ��������� ���������
 * @param out - �������� �����, ���� �������������� �����
 * @param set - ���������, ���������� ��������� ��������
 * @return - ������ �� �������� �����
 */
std::ostream& operator<<(std::ostream& out, const Set& set)
{
	Set::elem* curr = set.first_el;
	if (!curr) out << "-";
	while (curr)
	{
		out << curr->value;
		if (curr->next) out << ", ";
		curr = curr->next;
	}
	out << std::endl;
	return out;
}
