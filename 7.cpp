#include <loki/SmartPtr.h>
#include <iostream>

using namespace Loki;
using namespace std;

class TestClass{
	public:
		TestClass() {	cout << "Constructor of TestClass\n"; }
		TestClass(const TestClass&) { cout << "Copy Constructor of TestClass\n"; }
		~TestClass() {	cout << "Destructor of TestClass\n"; }

		void Create();
		void Write(const char* msg) { cout << "Log call: " << msg << endl; }
};

typedef SmartPtr<TestClass> DefaultSmartPtr;

int main()
{
	DefaultSmartPtr p1 = new TestClass;

	return 0;
}

// clang++ -std=c++11 -I. loki-0.1.7/src/SmartPtr.cpp loki-0.1.7/src/SmallObj.cpp loki-0.1.7/src/Singleton.cpp 7.cpp
