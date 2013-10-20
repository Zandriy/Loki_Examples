#define LOKI_FUNCTOR_IS_NOT_A_SMALLOBJECT 1

#include "loki/Functor.h"
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

int main()
{
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

	return 0;
}
