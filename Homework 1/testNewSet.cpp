//
//  testNewSet.cpp
//  Homework1
//
//  Created by Harsh Chobisa on 1/18/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//
#include "newSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class testNewSet
{
public:
    void test()
    {
        Set a(1000);   // a can hold at most 1000 distinct items
        Set b(5);      // b can hold at most 5 distinct items
        Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
        ItemType v[6] = {"1","2","3","4","5","6"};

        // No failures inserting 5 distinct items into b
        for (int k = 0; k < 5; k++)
            assert(b.insert(v[k]));

        // Failure if we try to insert a sixth distinct item into b
        assert(!b.insert(v[5]));

        assert(s.empty());
        ItemType x = "9876543";
        assert( !s.get(42, x)  &&  x == "9876543"); // x unchanged by get failure
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

        cerr << "All NewSet tests passed" << endl;


    }

    Set s;

};

int main()
{
    testNewSet t = testNewSet();
    t.test();
}
