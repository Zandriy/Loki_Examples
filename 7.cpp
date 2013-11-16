#include <loki/SmartPtr.h>
#include <iostream>
#include <string>

using namespace Loki;
using namespace std;

class Fruit
{
	public:
		Fruit(string spDesc, string fruit, int differ)
		 	: m_SP_description(spDesc)
			, m_Fruit(fruit)
			, m_Differ(differ)
	 	{
			cout << "Constructor of " << m_Fruit << "-" << m_Differ << " for " << m_SP_description << endl;
	 	}
		~Fruit()
	 	{
			cout << "Destructor of " << m_Fruit << "-" << m_Differ << " for " << m_SP_description << endl;
	 	}

		void Say() { cout << "I'm " << m_Fruit << "-" << m_Differ << " with " << m_SP_description << endl; }
	protected:
		string m_SP_description;
		string m_Fruit;
		int m_Differ;
};

class Apple : public Fruit
{
	public:
		Apple(string spDesc)
		 	: Fruit(spDesc, "Apple", s_Differ++)
		{}
	private:
		static int s_Differ;
};

int Apple::s_Differ = 0;

class Pear : public Fruit
{
	public:
		Pear(string spDesc)
		 	: Fruit(spDesc, "Pear", s_Differ++)
		{}
		Pear * Clone() 
		{
			return (new Pear(m_SP_description));
		}
	private:
		static int s_Differ;
};

int Pear::s_Differ = 0; 

/* defaut SmartPtr in Loki
	 template
	 <
	 typename T,
	 template <class> class OwnershipPolicy = RefCounted,
	 class ConversionPolicy = DisallowConversion,
	 template <class> class CheckingPolicy = AssertCheck,
	 template <class> class StoragePolicy = DefaultSPStorage,
	 template<class> class ConstnessPolicy = LOKI_DEFAULT_CONSTNESS
	 >
	 class SmartPtr;
 */

typedef SmartPtr<Apple> SP_Default;
typedef SmartPtr<Pear, DeepCopy> SP_DeepCopy;
typedef SmartPtr<Pear, DeepCopy, AllowConversion> SP_DeepCopy_AllowConversion;
typedef SmartPtr<Pear, DeepCopy, AllowConversion, AssertCheckStrict> SP_DeepCopy_AllowConversion_AssertCheckStrict;

int main()
{
	SP_Default a1;
	SP_Default a2;
  a1	= new Apple( "<RefCounted, DisallowConversion, AssertCheck, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
  a2	= new Apple( "<RefCounted, DisallowConversion, AssertCheck, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
	// a1 = NULL; // !!! Assert
	// Apple *a3 = a1; // !!! Copmpile error
	a1 = a2;
	a1->Say();
	a2->Say();

	cout << "====================================\n";

	SP_DeepCopy p1;
	SP_DeepCopy p2;
  p1	= new Pear( "<DeepCopy, DisallowConversion, AssertCheck, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
  p2	= new Pear( "<DeepCopy, DisallowConversion, AssertCheck, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
	// p1 = NULL; // !!! Assert
	// Pear *p3 = p1; // !!! Copmpile error
	p1 = p2;
	p1->Say();
	p2->Say();

	cout << "====================================\n";

	SP_DeepCopy_AllowConversion p3;
	SP_DeepCopy_AllowConversion p4;
  p3	= new Pear( "<DeepCopy, AllowConversion, AssertCheck, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
  p4	= new Pear( "<DeepCopy, AllowConversion, AssertCheck, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
	// p1 = NULL; // !!! Assert
	Pear *p5 = p3;
	p3 = p4;
	p3->Say();
	p4->Say();

	cout << "====================================\n";


	// SP_DeepCopy_AllowConversion_AssertCheckStrict p6; // Assert
	// SP_DeepCopy_AllowConversion_AssertCheckStrict p7; // Assert
  SP_DeepCopy_AllowConversion_AssertCheckStrict p6	= new Pear( "<DeepCopy, AllowConversion, AssertCheckStrict, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
  SP_DeepCopy_AllowConversion_AssertCheckStrict p7	= new Pear( "<DeepCopy, AllowConversion, AssertCheckStrict, DefaultSPStorage, LOKI_DEFAULT_CONSTNESS>" );
	// p1 = NULL; // !!! Assert
	Pear *p8 = p7;
	p6 = p7;
	p6->Say();
	p7->Say();

	cout << "====================================\n";

	return 0;
}

// clang++ -std=c++11 -I. loki-0.1.7/src/SmartPtr.cpp loki-0.1.7/src/SmallObj.cpp loki-0.1.7/src/Singleton.cpp 7.cpp
