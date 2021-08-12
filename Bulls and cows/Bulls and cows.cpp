#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
#include <iostream>
vector<char> offered(4);
vector<char> supposed(4);
bool keeper(vector<char> a);
bool init()
{
	bool l = false;
	while (!l)
	{
		char a = ' ';
		int counter = 0;
		for (int i = 0; i < offered.size(); i++)
		{
			cin >> a;
			offered[i] = a;
			counter++;
		}
		if (counter>4)
		{
			error("Wrong number of letters");
		}
		
		if (keeper(offered))
		{
			l = true;
		}
		
	}
	return true;
}
bool init_sup()
{
	cin.clear();
	char a = ' ';
	for (int i = 0; i < offered.size(); i++)
	{
		cin >> a;
		supposed[i] = a;
	}
	keeper(supposed);
	return true;
}


int bulls()
{
	int x = 0;
	for (int i = 0; i < offered.size(); i++)
	{
		if (offered[i]==supposed[i])
		{
			x++;
		}

	}
	return x;
}
int cows()
{
	int x = 0;
	for (int i = 0; i < offered.size(); i++)
	{
		for (int k = 0; k < supposed.size(); k++)
		{
			if ((offered[i]==supposed[k])&&(i!=k))
			{
				x++;
			}
		}
	}
	return x;
}
bool keeper(vector<char> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		for (int k = 0; k < a.size(); k++)
		{
			if (a[i] == a[k] && (k != i))
			{
				cout << "Try your initialization again!\n";
				return false;
			}
		}
	}
	return true;
}
int main()
try
{
	init();
	
	while (true)
	{
		
		init_sup();
		cout << bulls() << " - bulls	" 
			 << cows() << " - cows\n";
	}
	
}
catch (exception& e)
{
	cout << e.what();
}
