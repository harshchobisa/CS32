//
//  Set.cpp
//  Project2
//
//  Created by CLICC User on 1/23/19.
//  Copyright © 2019 CLICC User. All rights reserved.
//

#include "Set.h"
#include <iostream>

using namespace std;

Set::Set() //default constructor
{
    dummy.prev = nullptr;
    dummy.next = nullptr;
    
}

Set::Set(const Set &source) //copy constructor
{
    dummy.prev = nullptr;
    dummy.next = nullptr;
    Node *p = source.dummy.next;
    while (p != nullptr)
    {
        insert(p->value);
        p = p-> next;
    }
}

Set::~Set() //destructor, loops through all nodes and deletes them
{
    Node *p;
    p = dummy.next;
    while (p != nullptr)
    {
        Node *n = p->next;
        delete p;
        p = n;
    }
}

//assignment operator, deletes everything in current list
//then loops through and uses insert to copy over nodes
Set& Set::operator =(const Set& source)
{
    if (this == &source)
        return *this;
    Node *p = dummy.next;
    while (p != nullptr) //first delete everything in the current list
    {
        Node *n = p;
        p = p->next;
        delete n;
    }
    dummy.prev = nullptr;
    dummy.next = nullptr;
    p = source.dummy.next;
    while (p != nullptr)
    {
        insert(p->value);
        p = p-> next;
    }
    return *this;
}


bool Set::empty() const
{
    return(dummy.next == nullptr);
}

int Set::size() const //returns number of nodes in linked list
{
    Node *p = dummy.next;
    int counter = 0;
    while(p != nullptr)
    {
        counter++;
        p = p->next;
    }
    
    return counter;
}

bool Set::contains(const ItemType &value) const
{
    Node *p = dummy.next;
    while(p != nullptr)
    {
        if(p->value == value)
            return true;
        p = p->next;
    }
    return false;
}

//inserts a node containing value at the end of the linked list
//if the value is not already in the linked list
bool Set::insert(const ItemType &value)
{
    if(contains(value))
        return false;
    Node *n = new Node;
    n->value = value;
    Node *p = &dummy;
    while(p->next != nullptr)
    {
        p = p->next;
    }
    p->next = n;
    n->prev = p;
    n->next = nullptr;
    
    return true;
}

//erases a value in the set
bool Set::erase(const ItemType &value)
{
    if(!contains(value))
        return false;
    Node *p = dummy.next;
    while(p->value != value)
    {
        p = p->next;
    }
    p->prev->next = p->next;
    if (p->next != nullptr) //if the node is not the last node in the list
        p->next->prev = p->prev;
    delete p;
    return true;
}

//swaps two sets by swapping the dummy nodes
void Set::swap(Set &other)
{
    Node temp = other.dummy;
    other.dummy = dummy;
    dummy = temp;
    
}

//sets value to the item in the list that is greater than pos amount of items
bool Set::get(int pos, ItemType &value) const
{
    if (pos < 0  ||  pos >= size())
        return false;
    int counter = 0;
    Node *p = dummy.next;
    ItemType toCompare = p->value;
    do //loop through every value in list
    {
        Node *j = dummy.next;
        for(int x = 0; x < size(); x++) //compare every value in the list to toCompare
        {
            if (toCompare > j->value )
                counter ++;
            j = j->next;
        }
        if (counter == pos) //found value to return
        {
            value = toCompare;
            return true;
        }
        else //increment p, change toCompare, and keep iterating
        {
            counter = 0;
            p = p->next;
            if( p!= nullptr)
                toCompare = p->value;
        }
    } while(p != nullptr);
    cerr << "GET FUNCTION HAS AN ERROR!!!!!!!!!!!!!"; //function should never reach this point
    return false;
}

void Set::dump()
{
    Node *p = dummy.next;
    while(p != nullptr)
    {
        cerr << p->value << endl;
        p = p->next;
    }
}

//puts all unique values from s1 and s2 into result
void unite(const Set& s1, const Set& s2, Set& result) 
{
    Set temp = s1;
    
    for(int x = 0; x < s2.size(); x++)
    {
        ItemType check;
        s2.get(x, check);
        temp.insert(check);
    }
    
    result = temp;
}

//inserts all values that are in s1 and not in s2 into result
void subtract(const Set& s1, const Set& s2, Set& result)
{
    
    Set temp = Set();
    
    for(int x = 0; x < s1.size(); x++)
    {
        ItemType check;
        s1.get(x, check);
        if (s2.contains(check))
            continue;
        else
            temp.insert(check);
    }
    
    result = temp;
}

