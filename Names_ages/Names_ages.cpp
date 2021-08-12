// Names_ages.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace::std;
#include <iostream>
#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
class Bad_area {};
int area(int length, int width)
{
    if (length <= 0 || width <= 0) throw Bad_area{};
    return length * width;
}
    int main()
    {
        area(-5, 4);
}
    
