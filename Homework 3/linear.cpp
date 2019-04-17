//
//  linear.cpp
//  Homework3
//
//  Created by Harsh Chobisa on 2/6/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

bool anyTrue(const double a[], int n)
{
    if (n <= 0)
        return false;
    if (somePredicate(a[0]))
        return true;
    else
        return anyTrue(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n <= 0) return false;
    if (n == 1)
    {
        if (somePredicate(a[0]))
            return 1;
        else
            return 0;
    }

    return (countTrue(a, 1) + countTrue(a + 1, n-1));
}

int firstTrue(const double a[], int n)
{
    if (n<=0)
        return -1;
    if (somePredicate(a[0]))
        return 0;
    int r = firstTrue(a+1, n-1);
    if (r == -1)
        return -1;
    else
        return (1+r);  // This is incorrect.
}


int positionOfMin(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if (n == 1)
    {
        return 0;
    }
    int r = positionOfMin(a+1, n-1);

    if (a[0] < a[1+r])
        return 0;
    else
        return 1+r;
}

bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return true;
    if (n1 <= 0)
        return false;


    if (a2[0] == a1[0])
        return includes(a1+1, n1-1, a2+1, n2-1);
    if (a2[0] != a1[0])
        return includes(a1+1, n1-1, a2, n2);

    return false;
}

//int main()
//{
//    double arr2[] = {50, 40, 40};
//    double arr1[] = {10, 50, 40, 20, 50, 40, 30};
//    double arr3[] = {9, -14, -11};
//    double arr4[] = {9, 19, -11};
//
//
//    assert(anyTrue(arr3, 3));
//    assert(!anyTrue(arr2, 3));
//
//    assert(countTrue(arr3, 3) == 2);
//    assert(countTrue(arr4, 3) == 1);
//
//    assert(firstTrue(arr3, 3) == 1);
//    assert(firstTrue(arr4, 3) == 2);
//    assert(firstTrue(arr1, 7) == -1);
//
//
//    assert(positionOfMin(arr3, 3) == 1);
//    assert(positionOfMin(arr1, 7) == 0);
//
//    assert(includes(arr1, 7, arr2, 3));
//
//
//    cout << "Passed all tests" << endl;
//
//}

/////DISCUSSION PROBLEMS!!!!!!!
//int maxVal(double a[], int n)
//{
//    if (n == 1)
//    {
//        return a[0];
//    }
//    int r = maxVal(a+1, n-1);
//    if (a[0] > r)
//        return a[0];
//    else
//        return r;
//    //return max(a[0], maxVal(a+1, n-1));
//}
//
//bool ordered(double a[], int n)
//{
//    if (n==0)
//        return true;
//    if (n==1)
//        return true;
//    return(a[0] <= a[1] && ordered(a+1, n-1));
//}
//
//void insertInOrder(int elem, stack<int>& s)
//{
//    if (s.empty())
//    {
//        s.push(elem);
//        return;
//    }
//    if (s.top() >= elem)
//    {
//        s.push(elem);
//        return;
//    }
//    int t = s.top();
//    s.pop();
//    insertInOrder(elem, s);
//    s.push(t);
//}
//
//void sortStack(stack <int>& s)
//{
//    if (s.empty() || s.size() == 1)
//        return;
//    int t = s.top();
//    s.pop();
//    sortStack(s);
//    insertInOrder(t, s);
//}
//
//
