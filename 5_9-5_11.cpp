#define LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT 1

#include <loki/Functor.h>
#include <iostream>
#include <string>

using namespace Loki;
using namespace std;

class Parrot
{
	public:
		void Eat()
		{
			cout << "Tsk, knick, tsk...\n";
		}
		void Speak()
		{
			cout << "Oh Captain, my Captain!\n";
		}
};

const char* Fun(int i, int j)
{
	   cout << "Fun(" << i << ", " << j << ") called\n";
		 return "0";
}

int main()
{
	///// 5.9
	cout << "\n***** 5.9\n";
	Parrot geronimo;
	// Define two Functors
	Functor<void>
		cmd1(&geronimo, &Parrot::Eat),
		cmd2(&geronimo, &Parrot::Speak);
	// alternatively, Functor can have void as
	// its default R parameter
	// Invoke each of them
	cmd1();
	cmd2();

	///// 5.10
	cout << "\n***** 5.10\n";
	Functor<const char*, LOKI_TYPELIST_2(char, int)> f1(Fun);
	Functor<std::string, LOKI_TYPELIST_1(double)> f2(
			BindFirst(f1, 10));
	// Prints: Fun(10, 15) called
	f2(15);
	
	///// 5.11
	cout << "\n***** 5.11\n";
	Functor<void> chainF = Chain(cmd2, cmd1);
	chainF();
	chainF = Chain(cmd2, chainF);
	chainF = Chain(cmd2, chainF);
	chainF = Chain(cmd2, chainF);
	chainF();
	return 0;
}


// clang++ -std=c++11 -I. 5_9-5_11.cpp
