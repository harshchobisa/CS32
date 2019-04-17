//
//  History.hpp
//  Project 1
//
//  Created by Harsh Chobisa on 1/11/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int deathRecord[MAXZOMBIES][2];
    int numDead;
    int nRows;
    int nCols;
};

#endif /* History_hpp */
