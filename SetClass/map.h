#pragma once
#include "Set.h"

template <typename K, typename V>
struct pair
{
	K k;
	V v;
};

template <typename K, typename V>
class map :
    public set<pair<K, V>>
{
	map(K* keys, V* values);
};

template <typename K, typename V>
map<K, V>::map(K* keys, V* values)
{
	auto ksize = _msize(keys) / sizeof(keys[0]);
	auto vsize = _msize(values) / sizeof(values[0]);
	auto minsz = min(ksize, vsize);
	for (size_t i = 0; i<minsz; i++)
	{
		pair<K, V> p = { keys[i], values[i] };
		add(p);
	}
}

