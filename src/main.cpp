#include <iostream>
using namespace std;
#include "String.h"

void test_constructors_and_print()
{
    cout << "Constructor and operator << TESTS" << endl;
    String s("Hello World");
    cout << "\"" << s << "\"" << endl;
}

void test_assignment()
{
    cout << "Assignment TESTS" << endl;
}

void test_relationals()
{
    cout << "Relational TESTS" << endl;
}

void test_reverse()
{
    cout << "Reverse TESTS" << endl;
}

void test_concatenate()
{
    cout << "Concatenate TESTS" << endl;
}

void test_indexOf()
{
    cout << "indexOf TESTS" << endl;
}

int main()
{
    test_constructors_and_print();
    test_assignment();
    test_relationals();
    test_reverse();
    test_concatenate();
    test_indexOf();
    return 0;
}