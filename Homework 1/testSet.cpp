#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class testSet
{
public:
    void test()
    {
        assert(s.empty());
        ItemType x = "9876543";
        assert( !s.get(4, x)  &&  x == "9876543"); // x unchanged by get failure
        s.insert("123456789");
        assert(s.size() == 1);
        assert(s.get(0, x)  &&  x == "123456789");
        assert(s.erase("123456789"));

        Set t; //test swap function
        t.insert("1"); t.insert("2"); t.insert("3");
        s.insert("5");
        s.swap(t);
        assert(t.size() == 1 && s.size() == 3);
        ItemType y;
        assert(t.get(0, y) && y == "5");
        assert(s.get(0, y) && y == "1");
        assert(s.get(1, y) && y == "2");
        assert(s.get(2, y) && y == "3");

        assert(s.erase("3"));
        assert(!(s.erase("3"))); //cannot erase element not in s
        assert(s.contains("2"));
        assert(!(s.contains("3")));

        cerr << "Set passed all tests" << endl;
    }

    Set s;

};

int main()
{
    testSet t = testSet();
    t.test();
}
//
//#include "Set.h"
//#include <iostream>
//#include <string>
//#include <cassert>
//using namespace std;
//
//class testSet
//{
//public:
//    void test()
//    {
//        assert(s.empty());
//        ItemType x = 9876543;
//        assert( !s.get(4, x)  &&  x == 9876543); // x unchanged by get failure
//        s.insert(123456789);
//        assert(s.size() == 1);
//        assert(s.get(0, x)  &&  x == 123456789);
//        assert(s.erase(123456789));
//
//        Set t; //test swap function
//        t.insert(1); t.insert(2); t.insert(3);
//        s.insert(5);
//        s.swap(t);
//        assert(t.size() == 1 && s.size() == 3);
//        ItemType y;
//        assert(t.get(0, y) && y == 5);
//        assert(s.get(0, y) && y == 1);
//        assert(s.get(1, y) && y == 2);
//        assert(s.get(2, y) && y == 3);
//
//        assert(s.erase(3));
//        assert(!(s.erase(3))); //cannot erase element not in s
//        assert(s.contains(2));
//        assert(!(s.contains(3)));
//
//        cerr << "Set passed all tests" << endl;
//    }
//
//    Set s;
//
//};
//
//int main()
//{
//    testSet t = testSet();
//    t.test();
//}
