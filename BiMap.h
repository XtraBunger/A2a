#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H
    // Header guard

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
    // Include statments to include the required libraries

using namespace std;    // Remove need to put std::

int nextPrime( int n ); // Undefined function to find the next prime number

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

template <typename HashedObj>   // Create template of whats behing hashed as a template to allow it to conform to different variable types
class BiMap
{
  public:
    BiMap( int size = 101 ) : array( nextPrime( size ) ) 
        // Passes the size to nextPrime to ensure array size is prime after initalizing the hash table
      { makeEmpty( ); } // Makes all entries empty

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }
        // Function that finds if the table contains x, checks if the location findPos (cursor) end on is active with isActive
    void makeEmpty( )
    {
        currentSize = 0;    // Sets size to 0
        for( auto & entry : array )
            entry.info = EMPTY; // Empties each entry
    }
        // Empties the hash table

    bool insert( const HashedObj & x )  // Takes element by reference (copies)
    {
            // Insert x as active
        int currentPos = findPos( x );  // Sets current position to the cursor
        if( isActive( currentPos ) )
            return false;   // If the current position is active, that means x is already in the hash, do not put x in again by returning false

        if( array[ currentPos ].info != DELETED )
            ++currentSize;  // If the current pos is not deleted, increase the size (since if it has alr been added, size will have already been increased)

        array[ currentPos ].element = x;    // Set the element at the current pos to be x
        array[ currentPos ].info = ACTIVE;  // Set it to be active

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );
                // Does the current size of the table/number of elements exceed half of the total table size? If so rehash the elements
        return true;    // Return true to end function
    }
        // Inserts elements via copy
    
    bool insert( HashedObj && x )   // Takes rvalue reference, allowing the function to work with rvalues
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );   // Move instead of = (gives owership to hash table)
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
        // Inserts elemented via move, same as previous insert function but overloaded so it can take different inputs

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;
                // Uses the cursor to find the current pos of x, and if it is not active (empty or deleted), then stop the function
        array[ currentPos ].info = DELETED; // If it is active, set status to deleted
        return true;    // End function
    }
        // Delete funcion

    enum EntryType { ACTIVE, EMPTY, DELETED };  // Defines enum type named EntryType used to represent status/state of an entry

  private:
    struct HashEntry
    {
        HashedObj element;  // Element stored in hash table
        EntryType info; // Status of the element

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { } 
            // Constructor that copies data into 
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { } 
            // Constructor that moves data
    };
        // Define a struct named Hash Entry with 2 member variables and an overloaded constructor for Lvalue and Rvalue

    vector<HashEntry> array;    // Make an vector called array of type HashEntry (template at the moment, so it it'll adapt to its type)
    int currentSize;    // Initalize an int to control size

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }
        // Checks if the current position is active

    int findPos( const HashedObj & x ) const
    {
        int offset = 1; // Set offset (i) =1
        int currentPos = myhash( x ); // Set initial cursor to initial hash value

        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {   // Run while current pos is not empty or is not = x
            currentPos += offset;  // Add current probe value to cursor
            offset += 2;    // Increase i by 2
            if( currentPos >= array.size( ) )   
                currentPos -= array.size( );
                    // If current pos is creater than array size, subtract array size to go back to near start
        }
        return currentPos;  // Return position of cursor
    }
        // The cursor

    void rehash( )
    {
        vector<HashEntry> oldArray = array; // Save the current hash table

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );  // Doubles table size anre resizes to next prime number larger than twice the old size
        for( auto & entry : array )
            entry.info = EMPTY;
                // Clear new table
            // Copy table over
        currentSize = 0;    // Set size = 0
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }               // Iterates through the old array and moves each active element into the new table

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;  // Create a hash object called hf
        return hf( x ) % array.size( );
    }
        // The hash function
};

#endif
