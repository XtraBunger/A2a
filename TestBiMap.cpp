#include <iostream>
#include <string>
#include "BiMap.h"

using namespace std;

// Simple main
int main()
{
    BiMap<int, int> h1;
    BiMap<int, std::string> string;

    for (int i = 1; i < 4; i++) {
        h1.insert(i, i * 2);
    }
    // Insert some key-value pairs into h1 (But not enough to trigger a rehash)

    std::cout << "Array before rehashing";
    h1.ddisplay();
    h1.display();

    for (int i = 1; i < 4; i++) {
        h1.insert(i, i * 10);
    }
    // Test if dupe keys are added by adding same keys with different values

    std::cout << "Keys and values should remain the same, as dupe keyes are added, so they are ignored";

    h1.ddisplay();
    h1.display();
    // The new values should not be there, array should be the same as the first ddisplay and display call at lines 20-21

    h1.makeEmpty();
    std::cout << "Now empty array";
    h1.ddisplay();
    // Makes array empty and call both displays to prove it

    for (int i = 1; i < 4; i++) {
        h1.insert(i, i * 5);
    }
    // Insert new values, similar to the first one

    h1.removeKey(1);
    h1.ddisplay();
    std::cout << "Key 1 and val 5 removed\n";
    // Remove key 1 and associated value 5

    h1.removeVal(10);
    std::cout << "Val 10 and key 2 removed\n";
    h1.ddisplay();
    // Remove val 10 and its respective key 5

    std::cout << "The current size of the bimap is: " << h1.getSize() << '\n';
    h1.display();

    if (h1.containsKey(3)) {
        std::cout << "3 is indeed in the bimap as a key\n";
    }
    else {
        std::cout << "The number 3 (spelled t-h-r-e-e) does not exist in this bimap as a key\n";
    }

    if (h1.containsKey(30)) {
        std::cout << "30 is indeed in the bimap as a key\n";
    }
    else {
        std::cout << "The number 30 does not exist in this bimap as a key\n";
    }

    if (h1.containsVal(15)) {
        std::cout << "15 is indeed in the bimap as a value\n";
    }
    else {
        std::cout << "The number 15 does not exist in this bimap\n";
    }

    if (h1.containsVal(7)) {
        std::cout << "7 is indeed in the bimap as a value\n";
    }
    else {
        std::cout << "The number 7 does not exist in this bimap\n";
    }
    // Check code for vals that do and don't exist in the bimap

    std::cout << "The key associated with the value ""15"" is " << h1.getKey(15) << '\n';
    std::cout << "The key associated with the key ""3"" is " << h1.getVal(3);
    // Test getKey and getVal (should match up) with the inserted values so the pair of (3,15)

    h1.makeEmpty();

    for (int i = 1; i <= 5; i++) {
        string.insert(i, "Big " + to_string(i));
    }
    // Test rehash (This is bimap before rehash) and test adding strings as values
    string.ddisplay();

    for (int i = 6; i <= 11; i++) {
        string.insert(i, "Boss " + to_string(i));
    }
    // Test rehashing

    string.ddisplay();
    return 0;
}
