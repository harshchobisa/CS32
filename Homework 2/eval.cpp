//
//  eval.cpp
//  Homework2
//
//  Created by Harsh Chobisa on 2/4/19.
//  Copyright © 2019 Harsh Chobisa. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
#include "Set.h"

using namespace std;

int precedence(char c)
{
    if (c == '!')
        return 3;
    if (c == '&')
        return 2;
    if (c == '|')
        return 1;
    cerr << "BIG ERROR! SAD!";
    return -1;
}


bool convert(string infix, string &postfix)
{
    if (infix.size() == 0)
        return false;
    int counter = 0;
    for (int x = 0; x < infix.size(); x++)
    {
        if (infix[x] == '(')
            counter++;
        else if (infix[x] == ')')
            counter--;
    }
    if (counter !=0)
        return false;
    postfix = "";
    stack<char> ops;
    bool nextOperand = true;
    bool nextNot = true;
    bool nextAndOr = false;
    bool nextClosed = false;
    bool nextOpen = true;
    for (int x = 0; x < infix.size(); x++)
    {
        char ch = infix[x];
        switch (ch) {
            case '(':
                if(!nextOpen)
                    return false;
                ops.push(ch);
                nextOperand = true; nextNot = true; nextAndOr = false; nextClosed = false; nextOpen = true;
                break;
            case ')':
                if(!nextClosed)
                    return false;
                while (ops.top() != '(')
                {
                    postfix = postfix + ops.top();
                    ops.pop();
                }
                ops.pop();
                nextOperand = false; nextNot = false; nextAndOr = true; nextClosed = true; nextOpen = false;
                break;
            case ' ':
                break;
            case '!':
                if (!nextNot)
                    return false;
                while (!ops.empty() && ops.top() != '(' && precedence(ch) < precedence(ops.top())) //&& postfix.size() != 0)
                {
                    postfix = postfix + ops.top();
                    ops.pop();

                }
                ops.push(ch);
                nextOperand = true; nextNot = true; nextAndOr = false; nextClosed = false; nextOpen = true;
                break;
            case '|':
            case '&':
                if (!nextAndOr)
                    return false;
                while (!ops.empty() && ops.top() != '(' && precedence(ch) <= precedence(ops.top()))
                {
                    postfix = postfix + ops.top();
                    ops.pop();
                }
                ops.push(ch);
                nextOperand = true; nextNot = true; nextAndOr = false; nextClosed = false; nextOpen = true;
                break;
            default:
                if (!nextOperand)
                    return false;
                if(!(islower(ch)))
                    return false;
                postfix = postfix + ch;
                nextOperand = false; nextNot = false; nextAndOr = true; nextClosed = true; nextOpen = false;
                break;
        }
    }
    while (!ops.empty())
    {
        postfix = postfix + ops.top();
        ops.pop();
    }
    return true;
}



int setResult(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    stack<bool> ops;
    for (int x = 0; x < postfix.size(); x++)
    {
        char ch = postfix[x];
        bool operand2;
        bool operand1;
        switch (ch) {
            case '&':
                if (ops.size() < 2)
                    return 1;
                operand2 = ops.top();
                ops.pop();
                operand1 = ops.top();
                ops.pop();
                ops.push(operand1 && operand2);
                break;
            case '|':
                if (ops.size() < 2)
                    return 1;
                operand2 = ops.top();
                ops.pop();
                operand1 = ops.top();
                ops.pop();
                ops.push(operand1 || operand2);
                break;
            case '!':
                if (ops.size() < 1)
                    return 1;
                operand1 = ops.top();
                ops.pop();
                ops.push(!operand1);
                break;
            default:
                if(!trueValues.contains(ch) && !falseValues.contains(ch))
                    return 2;
                if(trueValues.contains(ch) && falseValues.contains(ch))
                    return 3;
                if(trueValues.contains(ch))
                    ops.push(true);
                if(falseValues.contains(ch))
                    ops.push(false);
                break;
        }
    }
    result = ops.top();
    return 0;
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    if (!convert(infix,postfix))
        return 1;
    int returnVal = setResult(infix, trueValues, falseValues, postfix, result);
    return returnVal;
}

//int main()
//{
//    string trueChars  = "tywz";
//    string falseChars = "fnx";
//    Set trues;
//    Set falses;
//    for (int k = 0; k < trueChars.size(); k++)
//        trues.insert(trueChars[k]);
//    for (int k = 0; k < falseChars.size(); k++)
//        falses.insert(falseChars[k]);
//
//    string pf;
//    bool answer;
//    assert(evaluate("w|f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
//    assert(evaluate("y|", trues, falses, pf, answer) == 1);
//    assert(evaluate("n t", trues, falses, pf, answer) == 1);
//    assert(evaluate("nt", trues, falses, pf, answer) == 1);
//    assert(evaluate("()", trues, falses, pf, answer) == 1);
//    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
//    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
//    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
//    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
//           &&  pf == "ff!tn&&|"  &&  !answer);
//    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
//    trues.insert('x');
//    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
//    falses.erase('x');
//    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
//    trues.erase('w');
//    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
//    falses.insert('w');
//    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
//    assert(evaluate("(w & f))", trues, falses, pf, answer) == 1);
//    assert(evaluate("((w & f)", trues, falses, pf, answer) == 1);
//    assert(evaluate("!!t", trues, falses, pf, answer) == 0  &&  pf == "t!!" &&  answer);
//    assert(evaluate("(n)()", trues, falses, pf, answer) == 1);
//    assert(evaluate("!", trues, falses, pf, answer) == 1);
//    assert(evaluate("2", trues, falses, pf, answer) == 1);
//    assert(evaluate("x!!", trues, falses, pf, answer) == 1);
//    assert(evaluate("x!", trues, falses, pf, answer) == 1);
//    assert(evaluate("!a!b!c", trues, falses, pf, answer) == 1);
//
//    string p = "";
//    convert("w|t&z", p);
//    cout << p;
//
//    cout << endl;
//    cout << "Passed all tests" << endl;
//}

