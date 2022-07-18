#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

template <class OBJ>
class Provider;

template <class OBJ>
class Factory
{
public:
	static Factory<OBJ> &getInstance()
	{
		static Factory<OBJ> obj;
		return obj;
	}
	void regist(Provider<OBJ> *provider)
	{
		m_map[provider->getName()] = provider;
	}
	Provider<OBJ> *getProvider(const std::string name)
	{
		Provider<OBJ> *test = m_map.find(name)->second;
		return dynamic_cast<typename OBJ::PROVIDER*>(test);
	}

private:
	std::map<std::string, Provider<OBJ> *> m_map;
};
