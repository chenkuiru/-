#include "LFUCache.h"

int LFUCache::get(int key)
{
	if (KeyToValue.find(key) == KeyToValue.end())
	{
		return -1;
	}
	increaseFreq(key);
	return KeyToValue[key];

}

void LFUCache::put(int key, int value)
{
	if (KeyToValue.find(key) != KeyToValue.end())
	{
		KeyToValue[key] = value;
		increaseFreq(key);
		return;
	}

	if (m_capacity <= KeyToValue.size())
	{
		if (m_capacity <= 0)
		{
			return;
		}
		removeMinFreq();
	}

	KeyToValue.insert(make_pair(key, value));
	KeyToFreq.insert(make_pair(key, 1));

	if (FreqToKey.find(1) == FreqToKey.end())
	{
		list<int> temp{ key };
		FreqToKey.insert(make_pair(1, temp));
	}
	else
	{
		//auto temp = FreqToKey[1];
		//temp.push_back(key);
		//FreqToKey[1] = temp;
		FreqToKey[1].push_back(key);
	}

	m_minFreq = 1;
}

void  LFUCache::increaseFreq(int key)
{
	int freq = KeyToFreq[key];

	KeyToFreq[key] = freq + 1;

	if (FreqToKey.find(freq + 1) == FreqToKey.end())
	{
		list<int> temp{ key };
		FreqToKey.insert(make_pair(freq + 1, temp));
	}
	else
	{
		//auto temp = FreqToKey[freq + 1];
		//temp.push_back(key);
		//FreqToKey[freq + 1] = temp;
		FreqToKey[freq + 1].push_back(key);
	}

	auto listTemp = FreqToKey[freq];
	listTemp.remove(key);
	if (listTemp.size() == 0)
	{
		FreqToKey.erase(freq);
		if (freq == m_minFreq)
		{
			m_minFreq ++;
		}
		
	}
	else
	{
		FreqToKey[freq] = listTemp;
	}


}
void  LFUCache::removeMinFreq()
{
	
	auto keylist = FreqToKey[m_minFreq];
	auto deleteKey = keylist.front();
	keylist.pop_front();

	if (keylist.empty())
	{
		FreqToKey.erase(m_minFreq);
	}
	else
	{
		FreqToKey[m_minFreq] = keylist;
	}
	KeyToValue.erase(deleteKey);
	KeyToFreq.erase(deleteKey);
}
