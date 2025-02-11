#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H
// Header guard

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
    // Include statments to include the required libraries

using namespace std;    // Remove need to put std::

int nextPrime(int n);

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

template <typename KeyType, typename ValType>   // Create template of whats behing hashed as a template to allow it to conform to different variable types

class BiMap
{
public:
    BiMap(int size = 11) : keyArray(nextPrime(size)), valArray(nextPrime(size))
        // Passes the size to nextPrime to ensure array size is prime after initalizing the hash table
    {
        makeEmpty();
    } // Makes all entries empty

    int getSize() const {
        int i{};
        for (auto& entry : keyArray) {
            if (entry.info == ACTIVE) {
                i++;
            }
        }
        return i;
    }

    void makeEmpty()
    {
        currentSize = 0;    // Sets size to 0
        for (auto& entry : keyArray)
            entry.info = EMPTY; // Empties each key
        for (auto& entry : valArray)
            entry.info = EMPTY; // Empties each key
    }
    // Empties the hash table

    bool insert(const KeyType& x, const ValType& y)  // Takes key by reference (copies)
    {
        // Insert x as active
        int currentPosKey = findPosKey(x);  // Sets current position to the cursor
        int currentPosVal = findPosVal(y);
        if (isActiveKey(currentPosKey) || isActiveVal(currentPosVal))
            return false;   // If the current position is active, that means x is already in the hash, do not put x in again by returning false

        if (keyArray[currentPosKey].info != DELETED)
            ++currentSize;  // If the current pos is not deleted, increase the size (since if it has alr been added, size will have already been increased)

        keyArray[currentPosKey].key = x;    // Set the key at the current pos to be x
        keyArray[currentPosKey].info = ACTIVE;  // Set it to be active
        keyArray[currentPosKey].value = y;

        valArray[currentPosVal].key = x;    // Set the key at the current pos to be x
        valArray[currentPosVal].info = ACTIVE;  // Set it to be active
        valArray[currentPosVal].value = y;

        // Rehash; see Section 5.5
        if (currentSize > keyArray.size() / 2)
            rehash();
        // Does the current size of the table/number of key exceed half of the total table size? If so rehash the key

        return true;    // Return true to end function
    }
    // Inserts key via copy

    bool insert(KeyType&& x, ValType&& y)   // Takes rvalue reference, allowing the function to work with rvalues
    {
        // Insert x as active
        int currentPosKey = findPosKey(x);  // Sets current position to the cursor
        int currentPosVal = findPosVal(y);
        if (isActiveKey(currentPosKey) || isActiveVal(currentPosVal))
            return false;   // If the current position is active, that means x is already in the hash, do not put x in again by returning false

        if (keyArray[currentPosKey].info != DELETED)
            ++currentSize;

        keyArray[currentPosKey].key = std::move(x);    // Set the key at the current pos to be x
        keyArray[currentPosKey].info = ACTIVE;  // Set it to be active
        keyArray[currentPosKey].value = std::move(y);

        valArray[currentPosVal].key = std::move(x);    // Set the key at the current pos to be x
        valArray[currentPosVal].info = ACTIVE;  // Set it to be active
        valArray[currentPosVal].value = std::move(y);

        if (currentSize > keyArray.size() / 2)
            rehash();
        // Rehash; see Section 5.5

        return true;
    }
    // Inserts key via move, same as previous insert function but overloaded so it can take different inputs

    bool containsKey(const KeyType& x) const
    {
        return isActiveKey(findPosKey(x));
    }
    // Function that finds if the table contains x, checks if the location findPos (cursor) end on is active with isActive

    bool containsVal(const ValType& x) const
    {
        return isActiveVal(findPosVal(x));
    }
    // Function that finds if the table contains x, checks if the location findPos (cursor) end on is active with isActive

    bool removeKey(const KeyType& x)
    {
        int currentPos = findPosKey(x);
        if (!isActiveKey(currentPos))
            return false;
        // Uses the cursor to find the current pos of x, and if it is not active (empty or deleted), then stop the function

        KeyType temp = keyArray[currentPos].key;
        keyArray[currentPos].info = DELETED; // If it is active, set status to deleted
        removeVal(temp);
        --currentSize;
        return true;    // End function
    }
    // Delete funcion

    bool removeVal(const ValType& x)
    {
        int currentPos = findPosVal(x);
        if (!isActiveVal(currentPos))
            return false;
        // Uses the cursor to find the current pos of x, and if it is not active (empty or deleted), then stop the function

        ValType temp = keyArray[currentPos].value;
        valArray[currentPos].info = DELETED; // If it is active, set status to deleted
        removeKey(temp);
        --currentSize;
        return true;    // End function
    }

    ValType getVal(const KeyType& x) const& {

        int currentPos = findPosKey(x);
        if (!isActiveKey(currentPos)) {
            return ValType();
        }
        return keyArray[currentPos].value;
    } 

    KeyType getKey(const ValType& x) const& {

        int currentPos = findPosVal(x);
        if (!isActiveVal(currentPos)) {
            return KeyType();
        }
        return valArray[currentPos].key;
    }
    // Check the KEY associated with VALUE (so checking for key with value)

    void ddisplay() {
        std::cout << "\nKey Array...\n\n";
        for (auto& entry : keyArray) {
            std::cout << "Key: " << entry.key << " Value: " << entry.value << '\n';

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
            std::cout << "\n\n";
        }

        std::cout << "\nValue Array...\n\n";
            for (auto& entry : valArray) {
                std::cout << "Key: " << entry.key << " Value: " << entry.value << '\n';

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
                std::cout << "\n\n";
            }

            std::cout << "Current size of both arrays is: " << currentSize << "\n\n";
    }

    int getSize() {
        return currentSize;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };  // Defines enum type named EntryType used to represent status/state of an entry

private:
    struct HashEntry
    {
        KeyType  key;  // The key
        EntryType info; // Status of the key
        ValType value; // The actual data stored

        HashEntry(const KeyType& e = KeyType{ }, EntryType i = EMPTY, const ValType& v = ValType{ }) : key{ e }, info{ i }, value{ v } { }
        // Constructor that copies data into 

        HashEntry(KeyType&& e, EntryType i = EMPTY, ValType&& v = ValType{}) : key{std::move(e)}, info{i}, value{std::move(v)} { }
        // Constructor that moves data
    };
    // Define a struct named Hash Entry with 2 member variables and an overloaded constructor for Lvalue and Rvalue

    vector<HashEntry> keyArray;    // Make an vector called array of type HashEntry (template at the moment, so it it'll adapt to its type)
    vector<HashEntry> valArray;
    int currentSize;    // Initalize an int to control size

    bool isActiveKey(int currentPos) const
    {
        return keyArray[currentPos].info == ACTIVE;
    }
    // Checks if the current position is active

    bool isActiveVal(int currentPos) const
    {
        return valArray[currentPos].info == ACTIVE;
    }

    int findPosKey(const KeyType& x) const
    {
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
    // The cursor

    int findPosVal(const ValType& x) const
    {
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

    void rehash()
    {

        vector<HashEntry> oldKeyArray = keyArray; // Save the current hash table
        vector<HashEntry> oldValArray = valArray;

        // Create new double-sized, empty table
        keyArray.resize(nextPrime(2 * oldKeyArray.size()));
        valArray.resize(nextPrime(2 * oldValArray.size()));  // Doubles table size anre resizes to next prime number larger than twice the old size

        for (auto& entry : keyArray)
            entry.info = EMPTY;
        // Clear new table
        
        for (auto& entry : valArray)
            entry.info = EMPTY;

    // Copy table over
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
        static hash<KeyType > hf;  // Create a hash object called hf
        return hf(x) % keyArray.size();
    }
    // The hash function
};

#endif
