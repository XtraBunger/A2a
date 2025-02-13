#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H
// Header guard

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
    // Include statments to include the required libraries

using namespace std;    // Remove need to put std::

bool isPrime(int n);
int nextPrime(int n);
    // Function forward definitions


// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename KeyType, typename ValType>   // Create template to allow keys and vals to handle different data types

class BiMap
{
public:
    BiMap(int size = 11) : keyArray(nextPrime(size)), valArray(nextPrime(size)) {
        // Passes the size to nextPrime to ensure array size is prime after initalizing the hash table
        makeEmpty();    // Makes all entries empty
    } 

    int getSize() const {
        int i{};
        for (auto& entry : keyArray) {
            if (entry.info == ACTIVE) {
                i++;
            }
        }
        return i;
    }
        // Function that gets the size of the array

    void makeEmpty() {
        currentSize = 0;    // Sets size to 0
        for (auto& entry : keyArray)
            entry.info = EMPTY; // Empties each key
        for (auto& entry : valArray)
            entry.info = EMPTY; // Empties each key
    }
    // Empties the bimap

    bool insert(const KeyType& x, const ValType& y)  {
        int currentPosKey = findPosKey(x);  
        int currentPosVal = findPosVal(y);
            // Takes 2 cursor positions, one for where x (key) should go and one where y(value) should go
        if (isActive(currentPosKey, keyArray) || isActive(currentPosVal, valArray))
            return false;  
            // If the current position is active, that means x is already in the bimap,  return false to end fuction

        if (keyArray[currentPosKey].info != DELETED)
            ++currentSize;  
            // If the current pos is not deleted, increase the size (since if it has already been added, size will have already been increased)

        keyArray[currentPosKey].key = x;    
        keyArray[currentPosKey].info = ACTIVE;  
        keyArray[currentPosKey].value = y;
            // Inserts the key and value to the keyArray, and sets their status to ACTIVE

        valArray[currentPosVal].key = x;    
        valArray[currentPosVal].info = ACTIVE;  
        valArray[currentPosVal].value = y;
            // Inserts the key and value to the valArray, and sets their status to ACTIVE

        // Rehash; see Section 5.5
        if (currentSize > static_cast<int>(keyArray.size()) / 2)
            rehash();
        // Does the current size of the table/number of key exceed half of the total table size? If so rehash the bimap

        return true;    // Return true to end function
    }
    // Inserts key via copy

    bool containsKey(const KeyType& x) const
    {
        return isActive(findPosKey(x), keyArray);
    }
    // Function that finds if the table contains x as a key, checks if the location findPos(cursor) is active

    bool containsVal(const ValType& x) const
    {
        return isActive(findPosVal(x), valArray);
    }
    // Function that finds if the table contains x as a value, checks if the location findPos(cursor) is active

    bool removeKey(const KeyType& x)
    {
        int currentPos = findPosKey(x);
        if (!isActive(currentPos, keyArray))
            return false;
        // Uses the cursor to find the current pos of x, and if it is not active (empty or deleted), then stop the function

        ValType temp = keyArray[currentPos].value;  // Create a temp variable to store the value
        keyArray[currentPos].info = DELETED; // If it is active, set status to deleted in keyArray

        currentPos = findPosVal(temp);  // Change cursor to the position of the same pair on the valArray
        valArray[currentPos].info = DELETED;    // Set status to deleted in valArray

        --currentSize;  // Make the bimap smaller
        return true;    // End function
    }
    // Delete funcion

    bool removeVal(const ValType& x)
    {
        int currentPos = findPosVal(x);
        if (!isActive(currentPos, valArray))
            return false;
        // Uses the cursor to find the current pos of x, and if it is not active (empty or deleted), then stop the function

        KeyType temp = valArray[currentPos].key;    // Create a temp variable to store the key
        valArray[currentPos].info = DELETED;    // If it is active, set status to deleted in the valArray

        currentPos = findPosKey(temp);  // Change cursor to the position of the same pair on the keyArray
        keyArray[currentPos].info = DELETED;    // Set status to deleted in keyArray

        --currentSize;  // Make the bimap smaller
        return true;    // End function
    }

    ValType getVal(const KeyType& x) const& {

        int currentPos = findPosKey(x); // Sets the cursor to the position of x in the keyArray
        if (!isActive(currentPos, keyArray)) {
            return ValType();
        }  
            // If this position is not active, that means there is no val there, so return an empty ValType
        return keyArray[currentPos].value;  // If there is something there, return whats stored in the value variable
    }

    KeyType getKey(const ValType& x) const& {

        int currentPos = findPosVal(x); // Sets the cursor to the position of x in the valArray
        if (!isActive(currentPos, valArray)) {
            return KeyType();
        }
            // If this position is not active, that means there is no key there, so return an empty KeyType
        return valArray[currentPos].key;    // If there is something there, return whats stored in the key variable
    }
    // Check the KEY associated with VALUE (so checking for key with value)

    void display() {
        for (auto& entry : keyArray) {
            if (entry.info == ACTIVE) {
                cout << "Key: " << entry.key << " Value: " << entry.value << '\n';
            }
        }
    }
        // Searches for active indexes, and if it is active print off the key and the value

    void ddisplay() {
        cout << "\nKey Array...\n";
        int i{};
        
        for (auto& entry : keyArray) {
            cout << "Index: " << i << " Key: " << entry.key << " Value: " << entry.value << " Status: ";
            i++;
            switch (entry.info) {
            case ACTIVE:
                cout << "ACTIVE";
                break;
            case EMPTY:
                cout << "EMPTY";
                break;
            default:
                cout << "DELETED";
                break;
            }
            cout << "\n";
        }

        cout << "\nValue Array...\n";
        i = 0;
        for (auto& entry : valArray) {
            cout << "Index: " << i << " Key: " << entry.key << " Value: " << entry.value << " Status: ";
            i++;

            switch (entry.info) {
            case ACTIVE:
                std::cout << "ACTIVE";
                break;
            case EMPTY:
                std::cout << "EMPTY";
                break;
            default:
                std::cout << "DELETED";
                break;
            }
            std::cout << "\n";
        }

        std::cout << "Current size of both arrays is: " << currentSize << "\n\n";
    }
        // The ddisplay prints off every index of the array, even the empty and deleted ones

    enum EntryType { ACTIVE, EMPTY, DELETED };  // Defines enum type named EntryType used to represent status/state of an entry

private:
    struct HashEntry
    {
        KeyType  key;  // The key
        EntryType info; // Status of the key
        ValType value; // The actual data stored

        HashEntry(const KeyType& e = KeyType{ }, EntryType i = EMPTY, const ValType& v = ValType{ }) : key{ e }, info{ i }, value{ v } { }
        // Constructor that copies data into 

        HashEntry(KeyType&& e, EntryType i = EMPTY, ValType&& v = ValType{}) : key{ std::move(e) }, info{ i }, value{ std::move(v) } { }
        // Constructor that moves data
    };
    // Define a struct named Hash Entry with 2 member variables and an overloaded constructor for Lvalue and Rvalue

    vector<HashEntry> keyArray;    // Make a vector called keyArray to store the pairs by hashing the keys
    vector<HashEntry> valArray;    // Make a vector called valArray to store the pairs by hashing the values
    int currentSize;    // Initalize an int to control size

    bool isActive(int currentPos, const vector<HashEntry> array) const
    {
        return array[currentPos].info == ACTIVE;
    }
    // Checks if the current position is active. Takes array as a argument so it can be used to check if the element is active for both valArrays and keyArrays


    int findPosKey(const KeyType& x) const {    // y = 0 for key, y = 1 for val

        int offset = 1; // Set offset (i) =1
        int currentPos = myhash(x); // Set initial cursor to initial hash value

        while (keyArray[currentPos].info != EMPTY &&
            keyArray[currentPos].key != x)
        {   // Run while current pos is not empty or is not = x
            currentPos = (currentPos + offset) % keyArray.size(); // Ensures wrapping around the array
            offset += 2;   // Increase i by 2
        }
        return currentPos;  // Return position of cursor

    }

    int findPosVal(const ValType& x) const {    // y = 0 for key, y = 1 for val

        int offset = 1; // Set offset (i) =1
        int currentPos = myhash(x); // Set initial cursor to initial hash value

        while (valArray[currentPos].info != EMPTY &&
            valArray[currentPos].value != x)
        {   // Run while current pos is not empty or is not = x
            currentPos = (currentPos + offset) % valArray.size(); // Ensures wrapping around the array
            offset += 2;   // Increase i by 2
        }
        return currentPos;  // Return position of cursor

    }

    // The cursor

    void rehash()
    {

        vector<HashEntry> oldKeyArray = keyArray; 
        vector<HashEntry> oldValArray = valArray;
            // Create new double-sized, empty table

        keyArray.resize(nextPrime(2 * oldKeyArray.size()));
        valArray.resize(nextPrime(2 * oldValArray.size()));  
            // Doubles table size anre resizes to next prime number larger than twice the old size

        for (auto& entry : keyArray)
            entry.info = EMPTY;

        for (auto& entry : valArray)
            entry.info = EMPTY;
            // Clear new tables
        
        currentSize = 0;    // Set size = 0

        for (auto& entry : oldKeyArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.key), std::move(entry.value));

        for (auto& entry : oldValArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.key), std::move(entry.value));
    }
    // Iterates through the old array and moves each active key into the new table

    template <typename hashs>
    size_t myhash(const hashs& x) const
    {
        static hash<hashs> hf;  // Create a hash object called hf
        return hf(x) % keyArray.size();
    }
    // The hash function. This hash uses template, so it can hash different data types such as char, int, string, etc...
};

#endif