#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
class ElementTypeDescription
{
public:
	static ElementTypeDescription &getInstance()
	{
		static ElementTypeDescription obj;
		return obj;
	}
	void AddTypeDescription(const std::string Type_name)
	{
		std::vector<std::string> Key_vec;
		m_map[Type_name] = Key_vec;
		elemType_vec.push_back(Type_name);
	}
	void AddKeyDescription(const std::string Type_name, const std::string Key)
	{
		if (m_map.find(Type_name)->first == "")
		{
			AddTypeDescription(Type_name);
		}
		m_map.find(Type_name)->second.push_back(Key);
	}
	std::vector<std::string> getKeyDescription(const std::string Type_name)
	{
		std::vector<std::string> a;
		if (m_map.count(Type_name) != 0)
		{
			a = m_map.find(Type_name)->second;
		}
		return a;
	}
	void CreateDescription()
	{
		AddTypeDescription("CH");
		AddKeyDescription("CH", "N");
		AddKeyDescription("CH", "PHYSMODEL");
		AddKeyDescription("CH", "COOLANT");
		///////
		AddTypeDescription("BVOL");
		AddKeyDescription("BVOL", "P");
		///////
		AddTypeDescription("SMASS");
		AddKeyDescription("SMASS", "GIN");
		AddKeyDescription("SMASS", "TIN");
		///////
		AddTypeDescription("BLJUN");
		AddKeyDescription("BLJUN", "TYPE");
		///////
		AddTypeDescription("CFD");
		AddKeyDescription("CFD", "SCHEME");
		AddKeyDescription("CFD", "VIS");
	}
	std::map<std::string, std::vector<std::string>> getMap()
	{
		return m_map;
	}
	std::vector<std::string> getVector()
	{
		return elemType_vec;
	}

private:
	std::map<std::string, std::vector<std::string>> m_map;
	std::vector<std::string> elemType_vec;
	ElementTypeDescription()
	{
		CreateDescription();
	};
};