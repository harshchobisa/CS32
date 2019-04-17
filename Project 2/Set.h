//
//  Set.hpp
//  Project2
//
//  Created by CLICC User on 1/23/19.
//  Copyright © 2019 CLICC User. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <stdio.h>
#include <string>

using ItemType = std::string;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set &source);
    Set& operator =(const Set& source);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump();
private:
    struct Node
    {
        ItemType value;
        Node* next;
        Node* prev;
    };
    Node dummy;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_hpp */
