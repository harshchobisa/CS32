//
//  History.cpp
//  Project 1
//
//  Created by Harsh Chobisa on 1/11/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
{
    numDead = 0;
    this->nRows = nRows;
    this->nCols = nCols;
}

bool History::record(int r, int c)
{
    if ((r > nRows) || (c > nCols))
        return false;
    deathRecord[numDead][0] = r;
    deathRecord[numDead][1] = c;
    numDead++;
    
    return true;
}

void History::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < nRows; r++)
        for (c = 0; c < nCols; c++)
            grid[r][c] = '.';
    
    // Indicate each zombie's position
    for (int k = 0; k < numDead; k++)
    {
        char& gridChar = grid[deathRecord[k][0]-1][deathRecord[k][1]-1];
        switch (gridChar)
        {
            case '.':  gridChar = 'A'; break;
            case 'Z':  break;
            default:   gridChar++; break;
        }
    }

    clearScreen();
    for (r = 0; r < nRows; r++)
    {
        for(c = 0; c < nCols; c++)
            cout << grid[r][c];
            cout << endl;
    }
    cout << endl;
}

