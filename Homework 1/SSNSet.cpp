//
//  SSNSet.cpp
//  Homework1
//
//  Created by Harsh Chobisa on 1/17/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>

using namespace std;

SSNSet::SSNSet()
{
}

bool SSNSet::add(unsigned long ssn)
{
    return m_nSet.insert(ssn);
}

int SSNSet::size() const
{
    return m_nSet.size();
}

void SSNSet::print() const
{
    for (int x = 0; x < m_nSet.size(); x++)
    {
        unsigned long nextVal;
        m_nSet.get(x, nextVal);
        cout << nextVal << endl;
    }
}

