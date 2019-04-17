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
        //tests the empty function
        assert(s.empty());
        //ItemType x = "9876543";
        s.insert("123456789");

        //tests the size function
        assert(s.size() == 1);
        s.insert("99810823");
        assert(s.size() == 2);

        //tests the insert function
        assert(!(s.insert("123456789"))); //cannot insert the same value twice
        Set n = Set();
        assert(n.insert("10")); //testing adding to an empty list
        assert(n.insert("20")); //testing adding to the end of a list
        n.insert("30");
        n.insert("40");
        n.insert("50");

        //tests the remove function
        assert(n.erase("10")); //testing erasing from the front of a list
        assert(n.erase("50")); //testing erasing the last item in a list
        assert(n.erase("30")); //testing erasing an item from the middle
        assert(!(n.erase("30"))); //cannot remove an item thats not in the list
        n.erase("40");
        assert(n.erase("20")); //testing deleting the last item in a list

        //tests the contains function
        assert(!(n.contains("20")));
        n.insert("60");
        assert(n.contains("60"));

        n.erase("60");
        n.insert("10");
        n.insert("20");
        n.insert("30");
        n.insert("40");
        n.insert("50");

        //tests the get function
        ItemType checker;
        assert(n.get(0, checker) && checker == "10");
        assert(n.get(1, checker) && checker == "20");
        assert(n.get(2, checker) && checker == "30");
        assert((!n.get(8, checker))); //returns false if pos is greater than list size
        assert((!n.get(-1, checker))); //returns false if pos is less than list size;
        assert((!n.get(n.size(), checker))); //returns false if pos is equal to list size;

        //test swap function
        Set t;
        t.insert("1"); t.insert("2"); t.insert("3");
        s = Set();
        s.insert("5");
        t.swap(s);
        assert(t.size() == 1 && s.size() == 3);
        ItemType y;
        assert(t.get(0, y) && y == "5");
        assert(s.get(0, y) && y == "1");
        assert(s.get(1, y) && y == "2");
        assert(s.get(2, y) && y == "3");

        //test assignment operator

        t = s;
        assert(t.get(0, y) && y == "1");
        assert(t.get(1, y) && y == "2");
        assert(t.get(2, y) && y == "3");

        //test copy constructor

        Set k = s;
        assert(k.get(0, y) && y == "1");
        assert(k.get(1, y) && y == "2");
        assert(k.get(2, y) && y == "3");

        //test unite

        Set j = Set();
        j.insert("3");
        j.insert("4");
        j.insert("5");
        Set r = Set();
        r.insert("100000");
        unite(k, j, r);
        assert(r.contains("1") && r.contains("2") && r.contains("3")
               && r.contains("4") && r.contains("5") && r.size()==5);

        //test unite for aliasing
        unite(k, j, j);
        assert(j.contains("1") && j.contains("2") && j.contains("3")
               && j.contains("4") && j.contains("5") && j.size()==5);

        //test subtract
        subtract(k, j, r);
        assert(r.size()==0);

        Set x = Set();
        x.insert("1");
        x.insert("2");
        x.insert("3");
        Set z = Set();
        z.insert("2");
        z.insert("3");
        z.insert("4");

        subtract(x, z, z);
        assert(z.contains("1") && z.size()==1);

        cerr << "Passed all tests" << endl;

////
////        Set a;
////        Set b;
////        ItemType v[6] = {"9","5","6","7","8","3"};
////
////        // No failures inserting 5 distinct items into b
////        for (int k = 0; k < 5; k++)
////            assert(b.insert(v[k]));
////
////        // Failure if we try to insert a sixth distinct item into b
////
////        a.operator=(b);//checks assignment operator
////        assert(a.size() == 5);
////        assert(b.size() == 5);
////        cout << "*a*" << endl;
////        a.dump();
////        cout << "*b*" << endl;
////        b.dump();
////
////        Set d;
////        d.insert("0");
////        d.insert("1");
////        d.insert("2");
////
////        a.operator=(d);
////        assert(a.size() == 3);//copies current size, not maximum
////        cout << "**** BEFORE SWAP*****" << endl;
////        cout << "*b*" << endl;
////        b.dump();
////        cout << "*d*" << endl;
////        d.dump();
////        d.swap(b);
////        cout << "**** AFTER SWAP*****" << endl;
////        cout << "*b*" << endl;
////        b.dump();
////        cout << "*d*" << endl;
////        d.dump();
////
////        Set e(b);//copy constructor test
////        cout << "*e*" << endl;
////        e.dump();
////
////        Set f = Set();
////        f.insert("10");
////        f.insert("20");
////        f.insert("30");
////        cout << "SET F: " << endl;
////        f.dump();
////        f.erase("10");
////        f.dump();
////        f.erase("30");
////        cout << endl;
////        f.dump();
////        f.erase("20");
////        cout << "CHECKPOINT";
////        f.dump();
////
////        cerr << "Set passed all tests" << endl;
//
////        Set s;
////        assert(s.empty());
////        ItemType a = "abc";
////        s.insert(a);
////        ItemType x = "arepa";
////        s.insert(x);
////        ItemType y = "dsf";
////        s.insert(y);
////        ItemType z = "dsf";
////        assert(!s.insert(z));
////        assert(s.size() == 3);
////        string value;
////        s.get(1, value);
////        assert(value == "arepa");
////        s.erase("dsf");
////        Set b(s);
////        assert(!b.empty());
////        assert(b.size() == 2);
////        Set c;
////        c.insert("hi");
////        assert(c.size() == 1);
////        c.erase("hi");
////        assert(c.size() == 0);
////
////        Set s1;
////        s1.insert("2");
////        s1.insert("8");
////        s1.insert("3");
////        s1.insert("9");
////        s1.insert("5");
////
////        Set s2;
////        s2.insert("6");
////        s2.insert("3");
////        s2.insert("8");
////        s2.insert("5");
////        s2.insert("10");
////
////        Set result;
////        unite(s1, s2, result);
////        // result.dump();
////        assert(result.contains("9"));
////        assert(result.contains("3"));
////        assert(result.contains("6"));
////        assert(result.contains("5"));
////        assert(result.contains("10"));
////        assert(result.contains("2"));
////        assert(result.contains("8"));
////        assert(result.size() == 7);
////
////        Set subtraction;
////        subtract(s1, s2, subtraction);
////        // subtraction.dump();
////        assert(subtraction.contains("9"));
////        assert(subtraction.contains("2"));
////        assert(subtraction.size() == 2);
////
    }

    Set s;

};

int main()
{
    testSet t = testSet();
    t.test();
}























//
//// tester.cpp
//// To test HW 1 Problem 5, uncomment the following line:
//#define TESTNEW
//
//#ifdef TESTNEW
//#include "Set.h"
//#else
//#include "Set.h"
//#endif
//
//#include <iostream>
//#include <cstdlib>
//#include <cassert>
//#include <string>
//#include <vector>
//#include <type_traits>
//
//using namespace std;
//
//static ItemType DUMMY = 123;
//static ItemType DEFAULT = 0;
//static ItemType ARRAY[6] = { 10, 20, 30, 40, 50, 60 };
//
//bool isPermutation(const Set& s, const ItemType a[], int n)
//{
//    if (s.size() != n)
//        return false;
//    vector<ItemType> b(n);
//    for (int i = 0; i < n; i++)
//        s.get(i, b[i]);
//    for (int j = 0; j < n; j++)
//    {
//        int i;
//        for (i = j; i < n; i++)
//        {
//            if (a[j] == b[i])
//            {
//                ItemType t = b[j];
//                b[j] = b[i];
//                b[i] = t;
//                break;
//            }
//        }
//        if (i == n)
//            return false;
//    }
//    return true;
//}
//
//const int SPEC_MAX = 200;
//
//void testone(int n)
//{
//    Set s;
//    switch (n)
//    {
//        default: {
//            cout << "Bad argument" << endl;
//        } break; case  1: {
//            assert((is_same<decltype(&Set::empty), bool (Set::*)() const>::value));
//        } break; case  2: {
//            assert((is_same<decltype(&Set::size), int (Set::*)() const>::value));
//        } break; case  3: {
//            assert((is_same<decltype(&Set::contains),
//                    bool (Set::*)(const ItemType&) const>::value));
//        } break; case  4: {
//            assert((is_same<decltype(&Set::get),
//                    bool (Set::*)(int, ItemType&) const>::value));
//        } break; case  5: {
//            assert(s.empty());
//        } break; case  6: {
//            assert(s.size() == 0);
//        } break; case  7: {
//            assert(!s.erase(DEFAULT)  &&  s.size() == 0);
//        } break; case  8: {
//            assert(!s.contains(DEFAULT));
//        } break; case  9: {
//            ItemType x = DUMMY;
//            assert(!s.get(0, x));
//        } break; case 10: {
//            ItemType x = DUMMY;
//            s.get(0, x);
//            assert(x == DUMMY);
//        } break; case 11: {
//            assert(s.insert(DUMMY));
//        } break; case 12: {
//            s.insert(DUMMY);
//            assert(!s.empty());
//        } break; case 13: {
//            s.insert(DUMMY);
//            assert(s.size() == 1);
//        } break; case 14: {
//            s.insert(DUMMY);
//            assert(s.contains(DUMMY));
//        } break; case 15: {
//            s.insert(DUMMY);
//            ItemType x = DEFAULT;
//            assert(s.get(0, x));
//        } break; case 16: {
//            s.insert(DUMMY);
//            ItemType x = DEFAULT;
//            s.get(0, x);
//            assert(x == DUMMY);
//        } break; case 17: {
//            assert(s.insert(DUMMY)  &&  !s.insert(DUMMY));
//        } break; case 18: {
//            s.insert(DUMMY);
//            s.insert(DUMMY);
//            assert(s.size() == 1);
//        } break; case 19: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            assert(!s.empty()   &&  s.size() == 2);
//        } break; case 20: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            ItemType x = DUMMY;
//            s.get(0, x);
//            assert(x == ARRAY[0]);
//        } break; case 21: {
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            ItemType x = DUMMY;
//            s.get(0, x);
//            assert(x == ARRAY[0]);
//        } break; case 22: {
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            ItemType x = DUMMY;
//            s.get(0, x);
//            ItemType y = DUMMY;
//            s.get(1, y);
//            assert(x == ARRAY[0]  &&  y == ARRAY[1]);
//        } break; case 23: {
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[4]);
//            s.insert(ARRAY[2]);
//            assert(s.size() == 5);
//        } break; case 24: {
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[4]);
//            s.insert(ARRAY[2]);
//            ItemType x;
//            for (int k = 0; k < 5; k++)
//            {
//                s.get(k, x);
//                assert(x == ARRAY[k]);
//            }
//        } break; case 25: {
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            assert(s.size() == 2);
//        } break; case 26: {
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            ItemType x;
//            for (int k = 0; k < 2; k++)
//            {
//                s.get(k, x);
//                assert(x == ARRAY[k]);
//            }
//        } break; case 27: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[4]);
//            assert(s.erase(ARRAY[3]));
//        } break; case 28: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[4]);
//            s.erase(ARRAY[3]);
//            assert(s.size() == 4);
//        } break; case 29: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[4]);
//            assert(s.erase(ARRAY[0])  &&  s.size() == 4);
//        } break; case 30: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[4]);
//            assert(s.erase(ARRAY[4])  &&  s.size() == 4);
//        } break; case 31: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[1]);
//            assert(s.erase(ARRAY[1])  &&  s.size() == 2);
//        } break; case 32: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[1]);
//            s.erase(ARRAY[3]);
//            assert(isPermutation(s, ARRAY, 3));
//        } break; case 33: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[3]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[3]);
//            s.erase(ARRAY[3]);
//            assert(isPermutation(s, ARRAY, 3));
//        } break; case 34: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            assert(!s.erase(ARRAY[4]));
//        } break; case 35: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            s.erase(ARRAY[4]);
//            assert(s.size() == 4);
//        } break; case 36: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.erase(ARRAY[0]);
//            s.erase(ARRAY[1]);
//            assert(s.size() == 0);
//        } break; case 37: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            ItemType x;
//            assert(!s.get(-1, x));
//        } break; case 38: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            ItemType x = DUMMY;
//            s.get(-1, x);
//            assert(x == DUMMY);
//        } break; case 39: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            ItemType x;
//            assert(! s.get(3, x));
//        } break; case 40: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            ItemType x = DUMMY;
//            s.get(3, x);
//            assert(x == DUMMY);
//        } break; case 41: {
//            s.insert(DEFAULT);
//            ItemType x = DUMMY;
//            s.get(0, x);
//            assert(s.size() == 1  &&  x == DEFAULT);
//        } break; case 42: {
//            s.insert(DEFAULT);
//            s.erase(DEFAULT);
//            assert(s.size() == 0  &&  !s.contains(DEFAULT));
//        } break; case 43: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.erase(ARRAY[1]);
//            assert(!s.contains(DEFAULT));
//        } break; case 44: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.erase(ARRAY[1]);
//            assert(s.contains(ARRAY[2]));
//        } break; case 45: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.erase(ARRAY[2]);
//            assert(s.size() == 2  &&  !s.contains(ARRAY[2]));
//        } break; case 46: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.erase(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            s.insert(ARRAY[3]);
//            assert(s.size() == 3  &&  s.contains(ARRAY[2])  &&
//                   s.contains(ARRAY[3]));
//        } break; case 47: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            {
//                Set s2;
//                s2.insert(ARRAY[3]);
//                s2.insert(ARRAY[4]);
//                s.swap(s2);
//                assert(s.size() == 2  &&  s2.size() == 3);
//            }
//        } break; case 48: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            {
//                Set s2;
//                s2.insert(ARRAY[3]);
//                s2.insert(ARRAY[4]);
//                s.swap(s2);
//                for (size_t k = 0; k < 3; k++)
//                {
//                    assert(!s.contains(ARRAY[k]));
//                    assert(s2.contains(ARRAY[k]));
//                }
//                for (size_t k = 3; k < 5; k++)
//                {
//                    assert(s.contains(ARRAY[k]));
//                    assert(!s2.contains(ARRAY[k]));
//                }
//            }
//        } break; case 49: {
//            for (size_t k = 0; k < SPEC_MAX; k++)
//                assert(s.insert(k));
//            assert(s.size() == SPEC_MAX);
//        } break; case 50: {
////            for (size_t k = 0; k < SPEC_MAX; k++)
////                assert(s.insert(k));
////            ItemType x = SPEC_MAX;
////            assert(!s.insert(x)  &&  s.size() == SPEC_MAX  &&  !s.contains(x));
//        } break; case 51: {
//            assert(s.insert(DUMMY));
//            for (size_t k = 0; k < 10*SPEC_MAX; k++)
//                assert(!s.insert(DUMMY));
//            assert(s.size() == 1);
//        } break; case 52: {
////            for (size_t k = 0; k < SPEC_MAX; k++)
////                assert(s.insert(k));
////            assert(!s.insert(SPEC_MAX));
////            s.erase(0);
////            assert(s.insert(SPEC_MAX+1));
////            assert(!s.insert(SPEC_MAX+2));
//#ifdef TESTNEW
//        } break; case 53: {
//            // This test checked that swap takes the same amount of time
//            // no matter how many items are in the Sets.
//        } break; case 54: {
//            const size_t CAPACITY = 2;
//            Set s2;
//            for (size_t k = 0; k < CAPACITY; k++)
//                assert(s2.insert(k));
////            assert(! s2.insert(CAPACITY));
//        } break; case 55: {
//            const size_t CAPACITY = SPEC_MAX*2;
//            Set s2;
//            for (size_t k = 0; k < CAPACITY; k++)
//                assert(s2.insert(k));
////            assert(! s2.insert(CAPACITY));
//        } break; case 56: {
//            // This test checked that the destructor deletes the dynamic array.
//        } break; case 57: {
//            // This test checked that Sets can be properly copied and destroyed.
//        } break; case 58: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            {
//                Set s2(s);
//                s2.insert(ARRAY[3]);
//                assert(s2.size() == s.size()+1);
//            }
//        } break; case 59: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            {
//                Set s2(s);
//                s2.insert(ARRAY[3]);
//                assert(isPermutation(s2, ARRAY, 4));
//            }
//        } break; case 60: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            s.insert(ARRAY[2]);
//            {
//                Set s2(s);
//                s2.insert(ARRAY[3]);
//                assert(isPermutation(s, ARRAY, 3));
//            }
//        } break; case 61: {
//            {
////                Set s2(2);
////                s2.insert(ARRAY[0]);
////                s2.insert(ARRAY[1]);
////                Set s3(s2);
////                assert(!s3.insert(ARRAY[2]));
//            }
//        } break; case 62: {
//            // This test checked that the assignment operator doesn't just
//            // copy a pointer.
//        } break; case 63: {
//            // This test checked that empty Sets can be assigned and properly
//            // destroyed.
//        } break; case 64: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            {
//                Set s2;
//                s2.insert(ARRAY[2]);
//                s2.insert(ARRAY[3]);
//                s2.insert(ARRAY[4]);
//                s2 = s;
//                s2.insert(ARRAY[5]);
//                assert(s2.size() == s.size()+1);
//            }
//        } break; case 65: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            {
//                Set s2;
//                s2.insert(ARRAY[3]);
//                s2.insert(ARRAY[4]);
//                s2.insert(ARRAY[5]);
//                s2 = s;
//                s2.insert(ARRAY[2]);
//                assert(isPermutation(s2, ARRAY, 3));
//            }
//        } break; case 66: {
//            s.insert(ARRAY[0]);
//            s.insert(ARRAY[1]);
//            {
//                Set s2;
//                s2.insert(ARRAY[3]);
//                s2.insert(ARRAY[4]);
//                s2.insert(ARRAY[5]);
//                s2 = s;
//                s2.insert(ARRAY[2]);
//                assert(isPermutation(s, ARRAY, 2));
//            }
//        } break; case 67: {
//            // This test checked that self-assignment doesn't change the
//            // number of items in existence.
//        } break; case 68: {
//            // This test checked that self-assignment doesn't change the Set.
//#endif
//        }
//    }
//}
//
//int main()
//{
//    //cout << "Enter test number: ";
//    for (int n = 1; n < 69; n++)
//    {
//    //int n;
//    //cin >> n;
//    testone(n);
//    cout << "Passed test number " << n << endl;
//    }
//}
