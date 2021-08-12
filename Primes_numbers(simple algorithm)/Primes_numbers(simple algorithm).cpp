
#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
#include <iostream>
vector <int> numbers;
vector <int> primes;
void Checker(int k) 
{
	int divisors = 0;
	for (int l = 1; l <=k; l++)
	{
		if (k%l==0)
		{
			divisors = divisors + 1;
		}
	}
	if (divisors==2)
	{
		primes.push_back(k);
	}
}
int main()
{
	int m = 0, max = 0;
	cin >> max;
	for (int x = 1; x <= max; x++)
	{
		numbers.push_back(x);
	}
	for (int k = 0; k < numbers.size(); k++)
	{
		Checker(k);
	}
	for (int i = 0; i < primes.size(); i++)
	{
		cout << primes[i]<<'\n';
		 m++;
	}
	cout << "The are " << m << " primes";
}
