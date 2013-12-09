#include <loki/Factory.h>
#include <iostream>
#include <string>

using namespace Loki;
using namespace std;

class Fruit
{
	public:
		virtual ~Fruit() = 0;

		virtual void Say() = 0;
};

Fruit::~Fruit() {}

class Apple : public Fruit
{
	public:
		virtual void Say() { cout << "I'm an Apple\n"; }
};

class Pear : public Fruit
{
	public:
		virtual void Say() { cout << "I'm a Pear\n"; }
};

Fruit* CreateApple() {return new Apple;}
Fruit* CreatePear() {return new Pear;}

Fruit* CloneApple(const Fruit* ref) {return new Apple( *((Apple*)(ref)) );}
Fruit* ClonePear(const Fruit* ref) {return new Pear( *((Pear*)(ref)) );}

enum FruitInd{
	APPLE,
	PEAR
};

#undef ENABLE_NEW_FACTORY_CODE
/*
template <      
class AbstractProduct,
			typename IdentifierType, 
			typename ProductCreator = AbstractProduct* (*)(),
			template<typename, class>                      
			class FactoryErrorPolicy = DefaultFactoryError  
		>
class Factory;
*/

typedef Factory<Fruit, FruitInd> Factory_t;

/*
template <
        class AbstractProduct,
        class ProductCreator =
            AbstractProduct* (*)(const AbstractProduct*),
        template<typename, class>
            class FactoryErrorPolicy = DefaultFactoryError
    >
class CloneFactory 
*/

typedef CloneFactory<Fruit> CloneFactory_t;

int main()
{
	// Factory Example
	Factory_t f;
	f.Register(APPLE,CreateApple);
	f.Register(PEAR,CreatePear);

	Fruit* a = f.CreateObject(APPLE);
	Fruit* p = f.CreateObject(PEAR);

	a->Say();
	p->Say();

	if (a) { delete a; a = NULL; }

	f.Unregister(APPLE);
	try {
		a = f.CreateObject(APPLE);
	}
	catch (std::exception &err)
	{
		std::cout << "ERROR: " << err.what() << std::endl;
	}

	if (a) { delete a; a = NULL; }
	if (p) { delete p; p = NULL; }

	f.Register(APPLE,CreateApple);
	f.Register(PEAR,CreatePear);
	a = f.CreateObject(APPLE);
	p = f.CreateObject(PEAR);

	// CloneFactory Example
	CloneFactory_t cf;
	Fruit* ca = NULL;
	Fruit* cp = NULL;
	try {
		ca = cf.CreateObject(a);
	}
	catch (std::exception &err)
	{
		std::cout << "ERROR: " << err.what() << std::endl;
	}

	cf.Register(typeid(Apple), CloneApple);
	cf.Register(typeid(Pear), ClonePear);

	ca = cf.CreateObject(a);
	cp = cf.CreateObject(p);

	ca->Say();
	cp->Say();

	if (a) { delete a; a = NULL; }
	if (p) { delete p; p = NULL; }
	if (ca) { delete ca; ca = NULL; }
	if (cp) { delete cp; cp = NULL; }

	return 0;
}

// clang++ -std=c++11 -I. loki-0.1.7/src/SmallObj.cpp loki-0.1.7/src/Singleton.cpp 8.cpp 
