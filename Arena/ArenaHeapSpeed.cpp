#include "Memory.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// aloca arena para 10 milhões de inteiros
const int Max = 10000000;
Arena fast{ Max, sizeof(int) };
int* p[Max];

int main()
{
    // ------------------------------------------------------------------
    // Heap
    // ------------------------------------------------------------------

    auto start = high_resolution_clock::now();
    for (int i = 0; i < Max; ++i)
    {
        p[i] = new int;
        *(p[i]) = i;
    }
    for (int i = 0; i < Max; ++i)
    {
        delete p[i];
    }
    auto end = high_resolution_clock::now();

    cout << "Heap:  ";
    cout.width(4);
    cout << right;
    cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;

    // ------------------------------------------------------------------
    // Arena
    // ------------------------------------------------------------------

    start = high_resolution_clock::now();
    for (int i = 0; i < Max; ++i)
    {
        p[i] = (int*)fast.New();
        *(p[i]) = i;
    }
    for (int i = 0; i < Max; ++i)
    {
        fast.Delete(p[i]);
    }
    end = high_resolution_clock::now();

    cout << "Arena: ";
    cout.width(4);
    cout << right;
    cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;
}