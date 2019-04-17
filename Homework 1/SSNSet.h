//
//  SSNSet.hpp
//  Homework1
//
//  Created by Harsh Chobisa on 1/17/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#ifndef SSNSet_h
#define SSNSet_h

#include "Set.h"

class SSNSet
{
public:
    SSNSet();          // Create an empty SSN set.

    bool add(unsigned long ssn);
    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.

    int size() const;  // Return the number of SSNs in the SSNSet.

    void print() const;
    // Write every SSN in the SSNSet to cout exactly once, one per
    // line.  Write no other text.

private:
    Set m_nSet;
    // Some of your code goes here.
};

#endif /* SSNSet_hpp */
