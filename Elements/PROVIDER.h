#pragma once
#include "FACTORY_TEST.h"

template <class OBJ>
class Provider
{
public:
	Provider(){};
	Provider(const std::string &name)
	{
		this->m_name = name;
		Factory<OBJ>::getInstance().regist(this);
	}
	virtual std::string getName() 
	{ 
		return m_name; 
	}
	//virtual OBJ* create(const std::string name) 
	//{ 
	//	return new OBJ; 
	//}
	//virtual OBJ *create() 
	//{ 
	//	return new OBJ; 
	//}

protected:
	std::string m_name;
};

template <class OBJ, int NBARG = 0>
class ConcreteProvider : public Provider<OBJ>
{
public:
	ConcreteProvider() {}
	ConcreteProvider(const std::string name) : Provider<OBJ>(name) {}
	virtual OBJ *create() { return new OBJ; };
};

template <class OBJ>
class ConcreteProvider<OBJ, 1> : public Provider<OBJ>
{
public:
	ConcreteProvider() {}
	ConcreteProvider(const std::string name) : Provider<OBJ>(name) {}
	typedef typename OBJ::ARG1 BASE_ARG1;
	virtual OBJ *create(BASE_ARG1 arg1)
	{ 
		return new OBJ; 
	}
};

template <class OBJ, class CONCRETE, int NBARG = 0>
class ObjectProvider : OBJ::PROVIDER
{
public:
	ObjectProvider(const std::string name) : OBJ::PROVIDER(name) {}
	virtual OBJ *create()
	{
		return new CONCRETE();
	}
};

template <class OBJ, class CONCRETE>
class ObjectProvider<OBJ, CONCRETE, 1> : OBJ::PROVIDER
{
public:
	ObjectProvider(const std::string name) : OBJ::PROVIDER(name) {}
	virtual OBJ *create(typename OBJ::ARG1 arg1)
	{
		CONCRETE *at = new CONCRETE(arg1);
		return at;
	}
};