#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
#include <iostream>
int permutation(int a, int b)
{
    if (a <= 0 || b <= 0)
    {
        error("Numbers must be positive and nonzero");
    }
    int previous = 0;
    int result = 1;
    int const different = (a - b);
    for (a; a > different; a--)
    {
        previous = a;
         result*= a;
        if (result < previous)
        {
            error("Very big result. We can not represent it, sorry!");
        }
    }
    return result;
}
int combination(int a, int b)
{
    if (a <= 0 || b <= 0)
    {
        error("Numbers must be positive and nonzero");
    }
    int result = permutation(a, b);
    for (b; b >= 1; b--)
    {
        result /= b;
    }
    return result;
}
bool perm_comb(string operation) {
    vector<string> permutation{ "Permutation", "Perm", "P", "permutation", "perm", "p" };
    vector<string> combination{ "Combination", "Comb", "C", "combination", "comb", "c" };

    for (int i = 0; i < combination.size(); i++)
    {
        if (operation == permutation[i])
        {
            return true;
        }
        if (operation == combination[i])
        {
            return false;
        }
    }
    error("Wrong operation");
}
int calculate(int x, int y, string operation)
{
    if (perm_comb(operation))
    {
        return permutation(x, y);
    }
    else
        return combination(x, y);
}



int main()
try
{
    while (true)
    {

        cout << "Enter values of 'a' and 'b' followed by operation {such as 6 3 Combination}\n";
        int a = 0, b = 0;
        string operation;
        cin >> a >> b >> operation;
        if (a <= 0 || b <= 0)
        {
            error("Numbers must be positive and nonzero");
        }
        cout << calculate(a, b, operation)<<'\n';
    }
}
catch (exception& e)
{
    cout << e.what();
}
