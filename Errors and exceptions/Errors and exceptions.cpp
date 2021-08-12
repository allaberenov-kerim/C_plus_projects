// Errors and exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
#include <iostream>
int main()
try
{
	
	vector<int> Integers;
	int summ = 0, N = 0;
	cout << "Please enter the number of values you want to sum : \n";
	cin>>N;
	cout << "Please enter some integers(press '|' to stop) :";
	int a = 0;
	while (cin >> a)
		{
			Integers.push_back(a);
		}
	for (int i = 0; i < N; i++)
	{
		summ = Integers[i] + summ;
	}
	cout << "Summ of " << N << " integers is " << summ;
}
catch(out_of_range)
{
	cout << "Out of range of vector 'Integers[]'";
}
catch (exception)
{
	cout << "The result can't be represented as an integer.";
}




/*void printing_roots(double a, double b, double c)			//convert Celsious to Kelvin
{	
	double D=0;
	D = (b * b) - 4 * a * c;
	cout << "D is - " << D << '\n';
	if (D<0)
	{
		error("D is less than zero. There are no roots of its.");
	}
	cout << "D is - " << D << '\n';
	double x1 = 0, x2 = 0;
	x1 = (-b + D )/ (2 * a);
	x2 = (-b - D) / (2 * a);
	cout << "x1= " << x1 << "	" << "x2= " << x2;
}
int main()
try
{
	double a = 0, b = 0, c = 0;
	cout << "Enter a,b and c of ax^2+bx+c=0 \n";
	cin >> a>>b>>c;
	printing_roots(a, b, c);
	keep_window_open();
	
	
	
}
catch (exception& e)
{
	cout << e.what();
	keep_window_open();
}*/
/*try {

	cout << "Success!\n";
	error("Bad code");

	
	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}*/