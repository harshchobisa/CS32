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
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = 'E';

    Coord down(sr + 1, sc);
    if(down.r() <= nRows - 1 && valueAt(maze, down) != 'E' && valueAt(maze, down) != 'X')
    {
        if (pathExists(maze, nRows, nCols, down.r(), down.c(), er, ec))
            return true;
    }

    Coord left(sr, sc-1);
    if(left.c() >= 0 && valueAt(maze, left) != 'E' && valueAt(maze, left) != 'X')
    {
        if (pathExists(maze, nRows, nCols, left.r(), left.c(), er, ec))
            return true;
    }

    Coord up(sr - 1, sc);
    if(up.r() >= 0 && valueAt(maze, up) != 'E' && valueAt(maze, up) != 'X')
    {
        if (pathExists(maze, nRows, nCols, up.r(), up.c(), er, ec))
            return true;
    }


    Coord right(sr, sc+1);
    if(left.c() <= nCols - 1 && valueAt(maze, right) != 'E' && valueAt(maze, right) != 'X')
    {
        if (pathExists(maze, nRows, nCols, right.r(), right.c(), er, ec))
            return true;
    }

    return false;
}

//
//int main()
//{
//    string maze1[10] = {
//        "XXXXXXXXXX",
//        "X...X....X",
//        "XX.X..XX.X",
//        "XX...X...X",
//        "X.X.X..XXX",
//        "X...X.X.XX",
//        "X.X.X....X",
//        "XXX.X.XX.X",
//        "X...X..X.X",
//        "XXXXXXXXXX",
//    };
//
//    string maze2[10] = {
//        "XXXXXXXXXX",
//        "X...X....X",
//        "XX.X..XX.X",
//        "XX...X...X",
//        "X.X.X..XXX",
//        "X...X.X.XX",
//        "X.X.X....X",
//        "XXX.X.XXXX",
//        "X...X..X.X",
//        "XXXXXXXXXX",
//    };
//
//    string maze3[10] = {
//        "XXXXXXXXXX",
//        "XXXXXXX..X",
//        "XX.......X",
//        "X..X....XX",
//        "X..X..XXXX",
//        "X..XXX.X.X",
//        "XX...X...X",
//        "X....XX..X",
//        "XXX.....XX",
//        "XXXXXXXXXX",
//    };
//
//    string maze4[10] = {
//        "XXXXXXXXXX",
//        "XXXXXXX..X",
//        "XX.....X.X",
//        "X..X....XX",
//        "X..X..XXXX",
//        "X..XXX.X.X",
//        "XX...X...X",
//        "X....XX..X",
//        "XXX.....XX",
//        "XXXXXXXXXX",
//    };
//
//    assert(pathExists(maze1, 10, 10, 1, 3, 8, 8));
//    assert(!pathExists(maze2, 10, 10, 1, 3, 8, 8));
//    assert(pathExists(maze3, 10, 10, 5, 6, 2, 8));
//    assert(!pathExists(maze4, 10, 10, 5, 6, 2, 8));
//
//    cerr << "All tests passed" << endl;
//}
