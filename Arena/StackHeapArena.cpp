#include "Memory.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// aloca arena para 1 milhão de inteiros
const int Max = 10000000;
Arena fast { Max, sizeof(int) };

void stack()
{
	int a = 5;
}

void heap()
{
	int * p = new int;
	*p = 5;
	delete p;
}

void arena()
{
	int * p = (int*) fast.New();
	*p = 5;
	fast.Delete(p);
}

int main()
{
	// ------------------------------------------------------------------
	// Stack
	// ------------------------------------------------------------------

	auto start = high_resolution_clock::now();
	for (int i = 0; i < Max; ++i)
		stack();
	auto end = high_resolution_clock::now();

	cout << "Stack: ";
	cout.width(4);
	cout << right; 
	cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;

	// ------------------------------------------------------------------
	// Heap
	// ------------------------------------------------------------------

	start = high_resolution_clock::now();
	for (int i = 0; i < Max; ++i)
		heap();
	end = high_resolution_clock::now();

	cout << "Heap:  "; 
	cout.width(4);
	cout << right;
	cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;

	// ------------------------------------------------------------------
	// Arena
	// ------------------------------------------------------------------

	start = high_resolution_clock::now();
	for (int i = 0; i < Max; ++i)
		arena();
	end = high_resolution_clock::now();

	cout << "Arena: ";
	cout.width(4);
	cout << right; 
	cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;
}