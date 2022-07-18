#pragma once

class Element
{
public:
	typedef ConcreteProvider<Element, 1> PROVIDER;
	typedef std::string ARG1;
	Element() {}
	Element(ARG1 arg)
	{
		type_name = arg;
	}
	int getUnic_id()
	{
		return unic_id;
	}
	void setUnic_id(int id)
	{
		unic_id = id;
	}
	int getUser_id()
	{
		return user_id;
	}
	void setUser_id(int id)
	{
		user_id = id;
	}
	int getNumber()
	{
		return number;
	}
	void setNumber(int num)
	{
		number = num;
	}
	std::string getType_name()
	{
		return type_name;
	}
	void setType_name(std::string type)
	{
		type_name = type;
	}
	std::string getKey(std::string key)
	{
		std::string a = "";
		if (keys.count(key) != 0)
		{
			a = keys.find(key)->second;
		}
		return a;
	}
	void setKey(const std::string key, std::string value)
	{
		keys[key] = value;
	}

private:
	int unic_id;
	int user_id;
	int number;
	std::map<std::string, std::string> keys;

protected:
	ARG1 type_name;
};