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
	//Мощность множества
	int cardinality = 0;
	//Список элементов (указатель на первый элемент)
	elem* first_el = nullptr;
	//Указатель на последний элемент списка
	elem* last_el = nullptr;
	//Вспомогательная функция для копирования списка элементов
	void copy_set(const set<T>& other);
	//Метод удаления элементов множества
	void clear_set();
public:
	//Пустой конструктор по умолчанию необходим для создания пустого множества
	set(){}
	//Конструктор с параметром для создания множества по набору элементов массива
	explicit set(T* elems);
	//Конструктор копирования
	set(const set<T>& other);
	//Деструктор
	~set();
	//Функция для добавления одного элемента в множество
	bool add(T elem);
	//Метод удаления элемента из множества
	bool remove(T elem);
	//Метод проверки наличия элемента во множестве
	bool is_in_set(T elem) const;

	//Оператор присваивания
	set<T>& operator=(const set<T>& other);
	//Оператор объединения множеств
	set<T> operator+(const set<T>& other) const;
	//Оператор пересечения множеств
	set<T> operator*(const set<T>& other) const;
	//Разность множеств
	set<T> operator/(const set<T>& other) const;
	//Симметрическая разность множств
	set<T> operator-(const set<T>& other) const;
	//Оператор индексирования
	T& operator[](int index);

	//Вывод элементов множества
	template <typename T2>
	friend std::ostream& operator<<(std::ostream& out, const set<T2>& set);
};

#include <corecrt_malloc.h>

/**
 * Вспомогательная функция для копирования элементов множества
 */
template <typename T>
void set<T>::copy_set(const set<T>& other)
{
	//Создание копии списка из множества other
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
 * Удаления списка элементов множества
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
 * Конструктор с параметром создает множество по массиву элементов
 * @param els - элементы массива, добавляемые во множество
 */
template <typename T>
set<T>::set(T* els)
{
	//Проверяем, что массив не пустой
	if (!els) return;
	//Вычисляем размер массива как его размер в байтах поделенный на размер 0го элемента
	auto sz = _msize(els) / sizeof * els;
	//Добавляем каждый элемент по очереди во множество
	for (size_t i = 0; i < sz; i++)
	{
		add(els[i]);
	}
}

/**
 * Конструктор копирования
 */
template <typename T>
set<T>::set(const set<T>& other) : cardinality(other.cardinality)
{
	copy_set(other);
}

/**
 * Деструктор. Вызывается при удалении экземпляра класса из памяти
 */
template <typename T>
set<T>::~set()
{
	clear_set();
}

/**
 * Метод добавления элемента в множество
 * @param el - добавляемый элемент
 * @return возвращает true, если элемент добавлен и false, если элемент уже был во множестве
 */
template <typename T>
bool set<T>::add(T el)
{
	//Проверка на наличие добавляемых элементов во множестве
	if (!is_in_set(el))
	{
		//Если элемент отсутствовал во множестве, выделяем память для хранения в списке
		elem* newel = new elem;
		//заполняем значение
		newel->value = el;
		//Если множество было пустым, то новый элемент становится первым и последним
		if (!first_el) first_el = last_el = newel;
		else {
			//Если во множестве были элементы, то добавляем новый элемент после последнего
			last_el->next = newel;
			last_el = newel;
		}
		//Увеличиваем мощность множества
		cardinality++;
		return true;
	}
	return false;
}

/**
 * Метод удаления элемента из множества
 * @param el - удаляемый элемент
 * @return - возвращает true, если элемент был удален, в противном случае - false;
 */
template <typename T>
bool set<T>::remove(T el)
{
	//Если списка нет (множество пустое), сразу выходим
	if (!first_el) return false;
	if (first_el->value == el)
	{
		//Если нужно удалить первый элемент
		elem* del = first_el;
		first_el = first_el->next;
		delete del;
		//Если первый элемент обнулился, то обнуляется и последний
		if (!first_el) last_el = nullptr;
		cardinality--;
		return true;
	}
	//Устанавливаем указатель на первый элемент
	elem* curr = first_el;
	//Пока не дойдем до предпоследнего элемента множества или элемента, значение которого
	//равно удаляемому значению
	while (curr->next && curr->next->value != el)
	{
		//переходим к следующему элементу
		curr = curr->next;
	}
	//Если есть следующий элемент, значит цикл остановился потому, что значение
	//следующего элемента было искомым
	if (curr->next)
	{
		//Удаляем элемент, следующий за текущим
		elem* del = curr->next;
		curr->next = curr->next->next;
		delete del;
		//Если новый следующий элемент для текущего стал пуст, значит
		//был удален последний элемент: обновляем соответствующий указатель.
		if (!curr->next) last_el = curr;
		cardinality--;
		return true;
	}
	return false;
}

/**
 * Метод проверки наличия элемента во множестве
 * @param el проверяемый на наличие во множестве элемент
 * @return возвращает true, если элемент присутствует во множестве и false, в противном случае
 */
template <typename T>
bool set<T>::is_in_set(T el) const
{
	//Устанавливаем указатель на первый элемент
	elem* curr = first_el;
	//Пока не выйдем за пределы списка элементов множества
	while (curr)
	{
		//Если найден элемент, возвращаем true
		if (curr->value == el) return true;
		//иначе переходим к следующему элементу
		curr = curr->next;
	}
	return false;
}

/**
 * Оператор присваивания
 */
template <typename T>
set<T>& set<T>::operator=(const set<T>& other)
{
	//Проверка на самоприсваивание
	if (this == &other) return *this;
	clear_set();
	cardinality = other.cardinality;
	copy_set(other);
	return *this;
}

/**
 * Объединение множеств
 * @param other - второе множество, с которым нужно произвести объединение
 * @return - новое объединенное множество
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
 * Оператор пересечения множеств
 * @param other второе множества для поиска пересечения
 * @return Пересечение множеств
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
 * Оператор для нахождения разности множеств
 * @param other - вычитаемое множство
 * @return Элементы множства, не содержащиеся в вычитаемом множестве
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
 * Оператор индексирования (лево- и правосторонний)
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
 * Оператор вывода на экран элементов множества
 * @param out - выходной поток, куда осуществляется вывод
 * @param set - множество, содержащее выводимые элементы
 * @return - ссылка на выходной поток
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