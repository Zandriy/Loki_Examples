#define LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT 1

#include "loki/Functor.h"
#include <iostream>
#include <string>

using namespace Loki;
using namespace std;

struct TestFunctor
{
	void operator() (int i, double d)
	{
		cout << "TestFunctor::operator()(" << i << ", " << d << ") called\n";
	}
};

void TestFunction(int i, double d)
{
	cout << "TestFunction(" << i << ", " << d << ") called\n";
}

void TestFunction(int i);

// Ignore arguments-not of interest
// in this example
const char* TestFunction(double, double)
{
	static const char buffer[] = "Hello, world! === const char* TestFunction(double, double) ===\n";
	// It's safe to return a pointer to a static buffer
	return buffer;
}

int main()
{
	///// 5.6
	cout << "\n***** 5.6\n";
	TestFunctor f;
	Functor<void, LOKI_TYPELIST_2(int, double)> cmd(f);
	cmd(4, 4.5);

	///// 5.7
	cout << "\n***** 5.7\n";
	// Typedef used for convenience
	typedef void (*TpFun)(int, double);
	// Method 1: use an initialization
	TpFun pF = TestFunction;
	Functor<void, LOKI_TYPELIST_2(int, double)> cmd1 (pF);
	cmd1(4, 4.5);
	// Method 2: use a cast
	Functor<void, LOKI_TYPELIST_2(int, double)> cmd2(
			static_cast<TpFun>(TestFunction)); // Ok
	cmd2(4, 4.5);

	///// 5.8
	cout << "\n***** 5.8\n";
	typedef const char* (*TpStrFun)(double, double);
	TpStrFun pStrF = TestFunction;
	Functor<string, LOKI_TYPELIST_2(int, int)> cmd3(pStrF);
	// Should print "world!"
	cout << cmd3(10, 10).substr(7);

	return 0;
}
