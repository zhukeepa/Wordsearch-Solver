#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <cmath>

#include "Globals.h"
#include "Array2D.h"
#include "Array2D.cpp"

#define SIZE 4

using namespace std;

void search(Array2D<char> const& array, string strArray[SIZE])
{
    StrLocMap foo;
    LocationData ld[SIZE];
    for (int i = 0; i < SIZE; ++i)
        foo.insert(make_pair(strArray[i],ld[i]));

    wsSolve(array, foo);

    for (int i = 0; i < SIZE; ++i)
    {
        cout << strArray[i] << endl;
        cout << foo[strArray[i]].coord.pX << ", ";
        cout << foo[strArray[i]].coord.pY << endl;
        cout << foo[strArray[i]].dir.dX << ", ";
        cout << foo[strArray[i]].dir.dY << endl << endl;
    }
}


int main()
{
    Array2D<char> test(6, 3);

    test(0, 0) = 'C';
    test(1, 0) = 'A';
    test(2, 0) = 'P';
    test(3, 0) = 'P';
    test(4, 0) = 'L';
    test(5, 0) = 'E';

    test(0, 1) = 'B';
    test(1, 1) = 'A';
    test(2, 1) = 'P';
    test(3, 1) = 'P';
    test(4, 1) = 'P';
    test(5, 1) = 'L';

    test(0, 2) = 'X';
    test(1, 2) = 'L';
    test(2, 2) = 'A';
    test(3, 2) = 'P';
    test(4, 2) = 'P';
    test(5, 2) = 'Q';

    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 6; ++x)
        {
            cout << test(x, y) << " ";
        }
        cout << endl;
    }

    string foo[SIZE] = {"CAPPLE", "BAPPPL", "XLAPPQ", "APP"};
    search(test, foo);
}
