#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
#include <iostream>
vector <int> numbers(4);
void print_b_c(int bull, int cow)	//printing the number of bulls and cows
{
	if (bull == 4)
		cout << "Congratulation! " << bull << " bulls" << '\n';
	else
		cout <<bull << "-bulls and "<<cow<<"-cows"<<'\n';
}
int array_checking(int x)		//checking array for non-repeated digits
{
	int k = 0;
	for (int n = 0; n < numbers.size(); n++)
	{
		if (numbers[n]==x)
		{
			k++;
		}
	}
	return k;
}
int digit_checking(int x)		//checking digit
{	//one argument at input
	if (x < 0 || x>9)
		error("Digit isn't suitable");	//give error if digit isn't suitable
	
	return x;
}
int main()
{
	int n = 0;
	cout << "Please enter seed 'n' -";
	cin >> n;
	
	while (2 > 0)
	{
		
		try
		{
			
			
			vector <int> numbers_pl(4);
			
			for (int x = 0; x < numbers.size(); x++)	//filling 'numbers' vector with suit random digits
			{
				srand(n);
				int b = randint(9);
				digit_checking(b);
				if (array_checking(b) == 0)
					numbers[x] = b;
				else
					throw(2);
			}



			int cow = 0;
			int bull = 0;
			while (bull != 4)
			{
				cout << "Enter 4 digits of player: ";
				for (int y = 0; y < numbers.size(); y++)	//filling player's numbers		
				{
					int b = 0;
					cin >> b;
					digit_checking(b);
					numbers_pl[y] = b;

				}

				bull = 0;
				cow = 0;
				for (int l = 0; l < numbers.size(); l++)
				{
					for (int i = 0; i < numbers_pl.size(); i++)
					{

						if (i == l && numbers[i] == numbers_pl[i])		//cout bulls
						{
							bull = bull + 1;
						}
						if (l != i && numbers[l] == numbers_pl[i])				//cout cows
						{
							cow = cow + 1;
						}

					}
				}										// cout the number of bulls and cows
				print_b_c(bull, cow);
			}

		}
		catch (exception& e)
		{
			cout << e.what()<<'\n';
		}
		catch (int) {}
	}
}