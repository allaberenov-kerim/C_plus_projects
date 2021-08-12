
#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
#include <iostream>
void Solver(double a, double b, double c)
{
    double D = b * b - 4 * a * c;
    if (D > 0)
    {
        cout << "x1=" << (b + sqrt(D)) / 2 * a;
        cout << "x2=" << (b - sqrt(D)) / 2 * a;
    }
    if (D==0)
    {
        cout << "x=" << (b / 2 * a);
    }
    if (D<0)
    {
        cout << "This equations wrong!";
    }

}
int main()
{
    double a = 0, b = 0, c = 0;
    cout << "a(x^2)+bx+c=0\n";
    cin >> a >> b >> c;
    Solver(a, b, c);
}

