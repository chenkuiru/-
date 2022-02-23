#pragma once
#include<unordered_map>
#include <list>
#include <iostream>

using namespace std;

class LFUCache
{
public:
	LFUCache(int capacity):m_capacity(capacity) {};
	int get(int key);
	void put(int key, int value);

private:
	void increaseFreq(int key);
	void removeMinFreq();

private:
	int m_capacity;
	unordered_map<int, int> KeyToValue;
	unordered_map<int, int> KeyToFreq;
	int m_minFreq = 0;
	unordered_map<int, list<int>> FreqToKey;
};

inline void testLFU()
{
	LFUCache cache(3);
	cache.put(1, 1);
	cache.put(2, 2);
	cache.put(3, 3);
	cache.put(4, 4);
	std::cout << "cache.get(4)=" << cache.get(4) << endl;
	std::cout << "cache.get(3)=" << cache.get(3) << endl;
	std::cout << "cache.get(2)=" << cache.get(2) << endl;
	std::cout << "cache.get(1)=" << cache.get(1) << endl;
	cache.put(5, 5);
	cout << "cache.get(1)=" << cache.get(1) << endl;
	cout << "cache.get(2)=" << cache.get(2) << endl;
	cout << "cache.get(3)=" << cache.get(3) << endl;
	cout << "cache.get(4)=" << cache.get(4) << endl;
	cout << "cache.get(5)=" << cache.get(5) << endl;
	

}

