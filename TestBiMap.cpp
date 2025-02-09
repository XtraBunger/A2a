#include <iostream>
#include "BiMap.h"
using namespace std;

// Simple main
int main()
{
    BiMap<int> h1;
    BiMap<int> h2;

    cout << "Checking... (no more output means success)" << endl;

    for (int i = 1; i < 7; i++) {
        h1.insert(i,1);
    }

    h2 = h1;

    for (int i = 1; i < 3; i++) {
        h2.removeKey(i);
    }

    std::cout << "\nTesting ddisplay on h1...\n";
    h1.ddisplay();

    std::cout << "\nTesting ddisplay on h2...\n";
    h2.ddisplay();

    if (h1.containsKey(3)) {
        std::cout << "It worked!!\n";
    }

    return 0;
}
