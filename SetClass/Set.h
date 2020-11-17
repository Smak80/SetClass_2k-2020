#pragma once
#include <iostream>

template <typename T>
class set
{
protected:
	struct elem
	{
		T value;
		elem* next = nullptr;
	};
	
private:
	//�������� ���������
	int cardinality = 0;
	//������ ��������� (��������� �� ������ �������)
	elem* first_el = nullptr;
	//��������� �� ��������� ������� ������
	elem* last_el = nullptr;
	//��������������� ������� ��� ����������� ������ ���������
	void copy_set(const set<T>& other);
	//����� �������� ��������� ���������
	void clear_set();
public:
	//������ ����������� �� ��������� ��������� ��� �������� ������� ���������
	set(){}
	//����������� � ���������� ��� �������� ��������� �� ������ ��������� �������
	explicit set(T* elems);
	//����������� �����������
	set(const set<T>& other);
	//����������
	~set();
	//������� ��� ���������� ������ �������� � ���������
	bool add(T elem);
	//����� �������� �������� �� ���������
	bool remove(T elem);
	//����� �������� ������� �������� �� ���������
	bool is_in_set(T elem) const;

	//�������� ������������
	set<T>& operator=(const set<T>& other);
	//�������� ����������� ��������
	set<T> operator+(const set<T>& other) const;
	//�������� ����������� ��������
	set<T> operator*(const set<T>& other) const;
	//�������� ��������
	set<T> operator/(const set<T>& other) const;
	//�������������� �������� �������
	set<T> operator-(const set<T>& other) const;
	//�������� ��������������
	T& operator[](int index);

	//����� ��������� ���������
	template <typename T2>
	friend std::ostream& operator<<(std::ostream& out, const set<T2>& set);
};

#include <corecrt_malloc.h>

/**
 * ��������������� ������� ��� ����������� ��������� ���������
 */
template <typename T>
void set<T>::copy_set(const set<T>& other)
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
template <typename T>
void set<T>::clear_set()
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
template <typename T>
set<T>::set(T* els)
{
	//���������, ��� ������ �� ������
	if (!els) return;
	//��������� ������ ������� ��� ��� ������ � ������ ���������� �� ������ 0�� ��������
	auto sz = _msize(els) / sizeof * els;
	//��������� ������ ������� �� ������� �� ���������
	for (size_t i = 0; i < sz; i++)
	{
		add(els[i]);
	}
}

/**
 * ����������� �����������
 */
template <typename T>
set<T>::set(const set<T>& other) : cardinality(other.cardinality)
{
	copy_set(other);
}

/**
 * ����������. ���������� ��� �������� ���������� ������ �� ������
 */
template <typename T>
set<T>::~set()
{
	clear_set();
}

/**
 * ����� ���������� �������� � ���������
 * @param el - ����������� �������
 * @return ���������� true, ���� ������� �������� � false, ���� ������� ��� ��� �� ���������
 */
template <typename T>
bool set<T>::add(T el)
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
template <typename T>
bool set<T>::remove(T el)
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
template <typename T>
bool set<T>::is_in_set(T el) const
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
template <typename T>
set<T>& set<T>::operator=(const set<T>& other)
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
template <typename T>
set<T> set<T>::operator+(const set<T>& other) const
{
	set res = *this;
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
template <typename T>
set<T> set<T>::operator*(const set<T>& other) const
{
	set res;
	elem* curr = (cardinality > other.cardinality) ? first_el : other.first_el;
	const set& ts = (cardinality > other.cardinality) ? other : *this;
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
template <typename T>
set<T> set<T>::operator/(const set<T>& other) const
{
	set res(*this);
	elem* curr = first_el;
	while (curr)
	{
		if (other.is_in_set(curr->value)) res.remove(curr->value);
		curr = curr->next;
	}
	return res;
}

template <typename T>
set<T> set<T>::operator-(const set<T>& other) const
{
	return (*this + other) / (*this * other);
}

/**
 * �������� �������������� (����- � ��������������)
 *
 */
template <typename T>
T& set<T>::operator[](int index)
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
template <typename T>
std::ostream& operator<<(std::ostream& out, const set<T>& s)
{
	typename set<T>::elem* curr = s.first_el;
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