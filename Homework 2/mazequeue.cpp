//
//  main.cpp
//  Homework2
//
//  Created by Harsh Chobisa on 2/3/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

char valueAt(string maze[], Coord c)
{
    return maze[c.r()][c.c()];
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> q;
    q.push(Coord(sr,sc));
    maze[sr][sc] = 'E';
    while(q.size() > 0)
    {
        Coord top = q.front();
        //cerr << top.r() << " , " << top.c() << endl;
        q.pop();
        if (top.r() == er && top.c() == ec)
            return true;
        
        Coord down(top.r() + 1, top.c());
        if(down.r() <= nRows - 1 && valueAt(maze, down) != 'E' && valueAt(maze, down) != 'X')
        {
            q.push(down);
            maze[down.r()][down.c()] = 'E';
        }
        
        Coord left(top.r(), top.c()-1);
        if(left.c() >= 0 && valueAt(maze, left) != 'E' && valueAt(maze, left) != 'X')
        {
            q.push(left);
            maze[left.r()][left.c()] = 'E';
        }
        
        Coord up(top.r() - 1, top.c());
        if(up.r() >= 0 && valueAt(maze, up) != 'E' && valueAt(maze, up) != 'X')
        {
            q.push(up);
            maze[up.r()][up.c()] = 'E';
        }
        
        Coord right(top.r(), top.c()+1);
        if(left.c() <= nCols - 1 && valueAt(maze, right) != 'E' && valueAt(maze, right) != 'X')
        {
            q.push(right);
            maze[right.r()][right.c()] = 'E';
        }
    }
    
    return false;
}

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X....X...X",
//        "X.XX.XX..X",
//        "XXX....X.X",
//        "X.XXX.XXXX",
//        "X.X...X..X",
//        "X...X.X..X",
//        "XXXXX.X.XX",
//        "X........X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 3,5, 8,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
