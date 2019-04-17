#include "SSNSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class testSSNSet
{
public:
    void test()
    {
        assert(s.size() == 0);
        s.add(1);
        assert(s.size() == 1);
        s.add(2);
        s.add(3);
        s.print();

        cerr << "SSNSet passed all tests" << endl;
    }

    SSNSet s;

};

int main()
{
    testSSNSet t = testSSNSet();
    t.test();
}
