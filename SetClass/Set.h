#pragma once
#include <ostream>

class Set
{
	struct elem
	{
		int value;
		elem* next = nullptr;
	};
	//Мощность множества
	int cardinality = 0;
	//Список элементов (указатель на первый элемент)
	elem* first_el = nullptr;
	//Указатель на последний элемент списка
	elem* last_el = nullptr;
	//Вспомогательная функция для копирования списка элементов
	void copy_set(const Set& other);
	//Метод удаления элементов множества
	void clear_set();
public:
	//Пустой конструктор по умолчанию необходим для создания пустого множества
	Set(){}
	//Конструктор с параметром для создания множества по набору элементов массива
	explicit Set(int* elems);
	//Конструктор копирования
	Set(const Set& other);
	//Деструктор
	~Set();
	//Функция для добавления одного элемента в множество
	bool add(int elem);
	//Метод удаления элемента из множества
	bool remove(int elem);
	//Метод проверки наличия элемента во множестве
	bool is_in_set(int elem) const;

	//Оператор присваивания
	Set& operator=(const Set& other);
	//Оператор объединения множеств
	Set operator+(const Set& other) const;
	//Оператор пересечения множеств
	Set operator*(const Set& other) const;
	//Разность множеств
	Set operator/(const Set& other) const;
	//Симметрическая разность множств
	Set operator-(const Set& other) const;
	//Оператор индексирования
	int& operator[](int index);

	//Вывод элементов множества
	friend std::ostream& operator<<(std::ostream& out, const Set& set);
};
