#include <std_lib_facilities.h>
#include <iostream>

int gct(int a, int b)
{
	while (b != 0)
	{
		int c=b;
		b=a% b;
		a = c;
	}
	return a;
}

class Rational
{
public:
	Rational(int num, int denom);
	Rational(int);

	int numerator;
	int denominator;

	void normalise();						//control rational number
	double double_cnv();						//convert rational number to double
};


Rational::Rational(int num, int denom) :numerator{ num }, denominator{denom}							//Rational constructor
{
	normalise();
	if (denom = 0) error("Wrong denominator! Denominator must have natural value.");					//denominator control
}

Rational::Rational(int num)
{
	Rational rat_num{ num,1 };
}


void Rational::normalise()
{
	if (denominator < 0)
	{
		denominator = -denominator;
		numerator = -numerator;
	}
	int num = numerator / gct(numerator, denominator);
	int denom = denominator / gct(numerator, denominator);
	numerator = num;
	denominator = denom;
}

double Rational::double_cnv()
{
	return double(numerator) / denominator;
}

Rational operator+(const Rational& rat_num1, const Rational& rat_num2)
{
	return Rational{ rat_num1.numerator * rat_num2.denominator + rat_num2.numerator * rat_num1.denominator, rat_num1.denominator * rat_num2.denominator };
}					//handle addition of rational numbers


Rational operator-(const Rational& rat_num1, const Rational& rat_num2)
{
	return Rational{ rat_num1.numerator * rat_num2.denominator - rat_num2.numerator * rat_num1.denominator, rat_num1.denominator * rat_num2.denominator };
}					//handle addition of rational numbers


Rational operator*(const Rational& rat_num1, const Rational& rat_num2)
{
	return Rational{ rat_num1.numerator * rat_num2.numerator, rat_num1.denominator * rat_num2.denominator };
}					//handle multiplication of rational numbers


Rational operator/(const Rational& rat_num1, const Rational& rat_num2)
{
	return Rational{ rat_num1.numerator * rat_num2.denominator, rat_num1.denominator * rat_num2.numerator };
}					//handle di  of rational numbers

bool operator==(const Rational& rat_num1, const Rational& rat_num2)
{
	return(rat_num1.numerator == rat_num2.numerator) && (rat_num1.denominator == rat_num2.denominator);
}

ostream& operator<<(ostream& os, const Rational& rat_num)
{
	return os << rat_num.numerator << "/" << rat_num.denominator;
}
/*
class Money
{
public:

	enum Currency
	{
		USD = 1, DKK
	};

	Money() :cents(0), cur(USD) { }
	Money(long int c) :cents(c), cur(USD) { }
	Money(int d, int c) :cents(d * 100 + c), cur(USD)
	{
		if (c >= 100) error("cents must be between 0 and 99");
	}
	Money(long int c, Currency cur) :cents(c), cur(cur) { }
	Money(int d, int c, Currency cur)
		:cents(d * 100 + c), cur(cur) { }

	int get_dollars() const { return cents / 100; }
	int get_cents() const { return cents % 100; }

	long int cents;
	Currency cur;
};
int rounding(double d)						//rounding 'd' until int
{
	int withoutrest = d;
	double rest = d-withoutrest;
	if (rest < 0.5)
		return withoutrest;
	if (rest > 0.5)
		return withoutrest + 1;
}

Money conversion(const Money& m)
{
	const double DKKtoUSD = 0.16;
	const double USDtoDKK = 6.26;
	if (m.cur == 1)
	{
		long int result=rounding(m.cents * USDtoDKK);
		return Money{ result,Money::DKK };
	}
	if (m.cur == 2)
	{
		long int result2 = rounding(m.cents * DKKtoUSD);
		return Money{ result2,Money::USD };;
	}
	error("Impossible conversion");
}



ostream& operator<<(ostream& os, const Money& money)
{	
	string curr;
	switch (money.cur)
	{
	case 1:
		curr = "USD";
		break;
	case 2:
		curr = "DKK";
		break;
	default:
		error("Not defined money's currency");
		break;
	}

	return os << "There is - " << curr<<" " << money.get_dollars() << "." << money.get_cents() << " cents" << '\n';
}

istream& operator>>(istream& is, Money& money)
{
	char h;
	string curr;
	while (cin >> h)
	{
		if (!isalpha(h)) { cin.putback(h); break; }
		curr += h;
	}
	
	if (!(curr == "USD" || curr == "DKK" || curr == "KYD"))  // oops: format error
		error("Not handling currency");

	int dollar = 0, cent = 0;
	char ch;
	is >> dollar >> ch >> cent;

	if ((cent < 0) || (dollar < 0)) error("Value of money must be a psitive number or null");			//get error if money less than 0

	if (curr == "USD") money.cur = Money::USD;
	if (curr == "DKK") money.cur = Money::DKK;

	if (ch != '.') error("There is no '.'(dot) between dollars and cents inputs ");
	if (cent / 100 > 0) error("Cent's interval from 0-99");

	if (cent < 10) cent *= 10;
	int summ = dollar * 100 + cent;
	money.cents = summ;
	return is;
}

//----------------------------------------------------------------------------------------------------
//overloading functions

Money operator+(const Money& money1, const Money& money2)				
{
	if (money1.cur==money2.cur)
		return Money(money1.cents + money2.cents,money1.cur);
	if (money1.cur!=money2.cur)
		return conversion(money1) + money2;
}

Money operator-(Money& money1, Money& money2)
{
	if (money1.cur == money2.cur)
		return Money(money1.cents - money2.cents, money1.cur);
	if (money1.cur != money2.cur)
		return Money(conversion(money1).cents- money2.cents, money2.cur);
}

Money operator*(const Money& money1, const int& number)								//multiplicate money on int
{
	return money1.cents * number;
}
Money operator*(const int& number, const Money& money1)								//multiplicate int on money
{
	return money1.cents * number;
}

int operator/(const Money& money1, const int& number)								//divide money on int
{
	return money1.cents / number;
}
*/
int main()
try
{
	/*
	Money wallet;
	Money m1;
	Money m2;


	cin >> m1;
	cin >> m2;

	cout << conversion(m1)<<'\n';
	cout << conversion(m1)<<'\n';

	cout << "Summ of m1+m2=" << m1 + m2<<'\n';
	cout << "Summ of m1+m2=" << m1 - m2 << '\n';
	*/
	Rational a{ 24,36 };
	cout << a;

}
catch (exception& e)
{
	cout << e.what();
}

