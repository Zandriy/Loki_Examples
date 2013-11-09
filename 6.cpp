#include <loki/Singleton.h>
#include <iostream>
#include <string>

using namespace Loki;
using namespace std;

class LogImpl{
	friend class CreateUsingNew<LogImpl>;
	public:
		void Create();
		void Write(const char* msg) { cout << "Log call: " << msg << endl; }
	private:
		LogImpl() = default;
		LogImpl(const LogImpl&) = delete;
		LogImpl& operator=(const LogImpl&) = delete;
		~LogImpl() {	cout << "Destructor of LogImpl\n"; }
};

typedef SingletonHolder<LogImpl, CreateUsingNew, SingletonWithLongevity> Log;

class KeyboardImpl{
	friend class CreateUsingNew<KeyboardImpl>;
	public:
		void Create();
		void Print() { cout << "I'm printing from KeyboardImpl\n"; Log::Instance().Write("KeyboardImpl::Print()"); }
	private:
		KeyboardImpl() = default;
		KeyboardImpl(const KeyboardImpl&) = delete;
		KeyboardImpl& operator=(const KeyboardImpl&) = delete;
		~KeyboardImpl() {	cout << "Destructor of KeyboardImpl\n"; Log::Instance().Write("KeyboardImpl::~KeyboardImpl()"); }
};

class DisplayImpl{
	friend class CreateUsingNew<DisplayImpl>;
	public:
		void Create();
		void Show() { cout << "I show from DisplayImpl\n"; Log::Instance().Write("DisplayImpl::Show()"); }
	private:
		DisplayImpl() = default;
		DisplayImpl(const DisplayImpl&) = delete;
		DisplayImpl& operator=(const DisplayImpl&) = delete;
		~DisplayImpl() {	cout << "Destructor of DisplayImpl\n"; Log::Instance().Write("DisplayImpl::~DisplayImpl()"); }
};

inline unsigned int GetLongevity(KeyboardImpl*) { return 1; }
inline unsigned int GetLongevity(DisplayImpl*) { return 1; }
inline unsigned int GetLongevity(LogImpl*) { return 2; }

typedef SingletonHolder<KeyboardImpl, CreateUsingNew, SingletonWithLongevity> Keyboard;
typedef SingletonHolder<DisplayImpl, CreateUsingNew, SingletonWithLongevity> Display;

int main()
{
	Keyboard::Instance().Print();
	Display::Instance().Show();
	Keyboard::Instance().Print();

	return 0;
}

// clang++ -std=c++11 -I. loki-0.1.7/src/Singleton.cpp 6.cpp
