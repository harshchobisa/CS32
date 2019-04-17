//
//  Set.cpp
//  Homework1
//
//  Created by Harsh Chobisa on 1/17/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <algorithm>

Set::Set()
{
    m_numItems = 0;
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
    if (this->contains(value) || m_numItems >= DEFAULT_MAX_ITEMS)
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
            if (x != DEFAULT_MAX_ITEMS-1)
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

    std::swap(*this, other);

}


void Set::dump() const
{
    for (int x = 0; x < m_numItems; x++)
    {
        std::cerr << m_set[x] << std::endl;
    }
}


