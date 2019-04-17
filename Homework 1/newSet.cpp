//
//  newSet.cpp
//  Homework1
//
//  Created by Harsh Chobisa on 1/18/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#include "newSet.h"

#include <iostream>
#include <algorithm>
using namespace std;

Set::Set(int maxNumberOfValues)
{
    m_numItems = 0;
    if(maxNumberOfValues < 0)
    {
        cout << "Cannot have a negative capacity!";
        exit(EXIT_FAILURE);
    }
    m_set = new ItemType[maxNumberOfValues];
    m_capacity = maxNumberOfValues;
}

Set::Set()
{
    m_numItems = 0;
    m_set = new ItemType[DEFAULT_MAX_ITEMS];
    m_capacity = DEFAULT_MAX_ITEMS;
}

Set::~Set()
{
    delete [] m_set;
}

Set::Set(const Set &source)
{
    m_numItems = source.m_numItems;
    m_capacity = source.m_capacity;
    m_set = new ItemType[source.m_numItems];
    for (int x = 0; x < source.m_numItems; x++)
    {
        m_set[x] = source.m_set[x];
    }
}

Set& Set::operator=(const Set &source)
{
    if (&source == this)
        return *this;
    delete [] m_set;
    m_set = new ItemType[source.m_numItems];
    for (int x = 0; x < source.m_numItems; x++)
        m_set[x]=source.m_set[x];
    m_numItems=source.m_numItems;
    m_capacity=source.m_capacity;
    return *this;
}


bool Set::empty() const
{
    return m_numItems == 0;
}

int Set::size() const
{
    return m_numItems;
}

bool Set::insert(const ItemType& value)
{
    if (this->contains(value) || m_numItems >= m_capacity)
        return false;
    m_set[m_numItems] = value;
    m_numItems++;
    return true;
}

bool Set::erase(const ItemType &value)
{
    if (!(this->contains(value)))
        return false;
    
    for (int x = 0; x < m_numItems; x++)
    {
        if (m_set[x] == value)
        {
            m_numItems--;
            if (x != m_capacity-1)
                for (int i = x; i < m_numItems; i++)
                    m_set[i] = m_set[i + 1];
        }
    }
    return true;
}

bool Set::contains(const ItemType& value) const
{
    for(int x=0; x < m_numItems; x++)
    {
        if (m_set[x] == value)
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    ItemType temp[DEFAULT_MAX_ITEMS];
    for (int x = 0; x < m_numItems; x++)
    {
        temp[x]=m_set[x];
    }
    std::sort(temp, temp + m_numItems);
    if(i >= 0 && i <= this->size())
    {
        value = temp[i];
        return true;
    }
    
    return false;
    
}

void Set::swap(Set& other)
{
    ItemType* ptr;

    ptr = m_set;
    m_set = other.m_set;
    other.m_set = ptr;
    
    
    int temp = m_numItems;
    m_numItems = other.m_numItems;
    other.m_numItems = temp;
    
    temp = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = temp;
    
}


void Set::dump() const
{
    for (int x = 0; x < m_numItems; x++)
    {
        std::cerr << m_set[x] << " ";
    }
    std::cout << "size: " << m_numItems << std::endl;
    std::cout << "max size: " << m_capacity << std::endl;
}
