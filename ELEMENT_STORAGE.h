#pragma once
#include "Elements\\PROVIDER.h"
#include "Elements\\ELEMENT.h"
#include "k_parser.h"

using namespace std;

std::ostream &operator<<(std::ostream &out, Element &elem)
{
	unsigned int i;
	std::vector<std::string> keys_v = ElementTypeDescription::getInstance().getKeyDescription(elem.getType_name());
	out << "Type Name: " << elem.getType_name() << "\n"
		<< "User ID: " << elem.getUser_id() << "\n"
		<< "Unic ID: " << elem.getUnic_id() << "\n"
		<< "Number of objects: " << elem.getNumber() << "\n"
		<< "Keys of the object: "
		<< "\n";

	for (i = 0; i < keys_v.size(); i++)
	{
		if (elem.getKey(keys_v[i]) != "")
		{
			out << keys_v[i] << ": " << elem.getKey(keys_v[i]) << "\n";
		}
	}
	out << "____________________\n";
	return out;
}

class ElementStorage
{
public:
	static ElementStorage &getInstance()
	{
		static ElementStorage obj;
		return obj;
	}
	void addToStorage(int unicID, Element *elem)
	{
		m_elements[unicID]=elem;
	}
	std::map<int,Element*> getStorage()
	{
		return m_elements;
	}
	void emptyStorage()
	{
		for (unsigned int i = 0;i<m_elements.size();i++)
		{
			delete m_elements.find(i+1)->second;
		}
		m_elements.clear();
	}
	void createElements(Parser &parser)
	{
		Element *elem;
		for (int i = 0; i < parser.get_elems_count(); i++)
		{
			string typeName = parser.get_elem_typename();
			elem = Factory<Element>::getInstance().getProvider(typeName)->create(typeName);
			elem->setUser_id(parser.get_elem_user_id());
			elem->setNumber(parser.get_elem_number());
			for (int j = 0; j < parser.get_keys_count(); j++)
			{
				pair<string, string> key = parser.get_key_pair();
				elem->setKey(key.first, key.second);
			}
			elem->setUnic_id(parser.get_unic_id());
			ElementStorage::getInstance().addToStorage(parser.get_unic_id(),elem);
		}
	}
	void printAllElements()
	{
		Element *elem;
		for (unsigned int i = 0; i < (m_elements.size()); i++)
		{
			elem = m_elements.find(i+1)->second;
			std::cout << *elem;
		}
	}

private:
	std::map<int,Element*> m_elements;
	ElementStorage(){};
};