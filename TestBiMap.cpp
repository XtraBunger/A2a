#include <iostream>
#include <string>
#include "BiMap.h"
using namespace std;

// Simple main
int main()
{
    BiMap<int, int> h1;
    BiMap<int, std::string> string;

    // Insert some key-value pairs into h1
    for (int i = 1; i < 4; i++) {
        h1.insert(i, i * 2);
    }

    std::cout << "Array before rehashing";
    h1.ddisplay();

    for (int i = 1; i < 4; i++) {
        h1.insert(i, i * 5);
    }
    // Test adding dupe keys

    if (h1.getSize() < 4) {
        std::cout << "Dupe keys not added\n";
    }
    else {
        std::cout << "Error has occured";
        return -1;
    }

    h1.ddisplay();

    for (int i = 4; i < 14; i++) {
        h1.insert(i, i * 2);
    }
    // Rehash test

    std::cout << "Results of rehash\n";
    h1.ddisplay();

    int x = 4;

    std::cout << "Does the array contain this key? x: " << x << '\n';
    if (h1.containsKey(x)) {
        std::cout << "Yes\n";
    }
    else {
        std::cout << "No\n";
    }

    std::cout << "Does the array contain this value? x: " << x << '\n';
    if (h1.containsVal(x)) {
        std::cout << "Yes\n";
    }
    else {
        std::cout << "No\n";
    }

    std::cout << "Does the array contain this key? x: " << x + 100 << '\n';
    if (h1.containsVal(x + 100)) {
        std::cout << "Yes\n";
    }
    else {
        std::cout << "No\n";
    }

    std::cout << "Does the array contain this value? x: " << x + 100 << '\n';
    if (h1.containsVal(x + 100)) {
        std::cout << "Yes\n";
    }
    else {
        std::cout << "No\n";
    }

    for (int i = 5; i < 8; i++) {
        h1.removeKey(i);
    }
    std::cout << "Results of removing keys 5 to 8\n";
    h1.ddisplay();

    for (int i = 2; i < 5; i++) {
        h1.removeVal(i);
    }
    std::cout << "Results of removing values 4,6,8\n";
    h1.ddisplay();

    std::cout << "Readding key 2 and value 4 with different value/key to test replacement";
    h1.insert(2, 100);
    h1.insert(15, 4);
    h1.ddisplay();

    x = 2;
    std::cout << "The value associated with key " << x << " is: " << h1.getVal(x) << '\n';

    x += 2;
    std::cout << "The key associated with value " << x << " is: " << h1.getKey(x) << '\n';

    string.insert(1, "Jommy");
    string.insert(5, "Wow");

    string.ddisplay();

    std::cout << "Testing normal display...\n";

    string.display();

    if (string.containsVal("Wow")) {
        std::cout << "\nYes\n";
    }
    else {
        std::cout << "\nNo\n";
    }

    string.removeKey(1);
    string.display();

    string.insert(4, "Frankly");
    string.insert(16, "Umstroke");

    string.removeVal("Wow");

    string.display();

    return 0;
}
