//
//  newSet.hpp
//  Homework1
//
//  Created by Harsh Chobisa on 1/18/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#ifndef newSet_h
#define newSet_h

#include <stdio.h>
#include <string>

using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 250;

class Set
{
public:
    Set();
    
    Set(int maxNumberOfValues);         // Create an empty set (i.e., one with no items).
    
    ~Set();
    
    Set(const Set &source); //copy constructor
    
    Set& operator=(const Set &source); //assignment operator
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    void dump() const;
private:
    ItemType *m_set;
    int m_numItems;
    int m_capacity;
};


#endif /* newSet_hpp */