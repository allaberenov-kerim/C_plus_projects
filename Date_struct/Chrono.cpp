#include "Chrono.h"
#include <std_lib_facilities.h>
namespace Chrono {

	// member function definitions:


	Date::Date(int yy, Month mm, int dd)
		: y(yy), m(mm), d(dd)
	{
		if (!is_date(yy, mm, dd)) error("Invalid()");
	}

	const Date& default_date();

	Date::Date()
		:y(default_date().year()),
		m(default_date().month()),
		d(default_date().day())
	{
	}

	int days_in_month(int y, Date::Month m);

	void Date::add_day(int n)
	{
		// use linear_day() below or things get really messy
		if (n < 0) error("add_day(): can't handle negative n");	// not yet
		while (days_in_month(y, m) < n) {	// move one month at a time
			add_month(1);
			n -= days_in_month(y, m);
		}
		d += n;
	}


	void Date::add_month(int n)
	{
		if (n < 0) error("add_month(): cnot implemented");	// not yet
		// ...
	}


	void Date::add_year(int n)
	{
		if (m == February && d == 29 && !leapyear(y + n)) { // beware of leap years!
				// makes sense for both positive and negative n (n==0 should be impossible here)
			m = March;        // use March 1 instead of February 29
			d = 1;
		}
		y += n;
	}

	//------------------------------------------------------------------------------

	// helper functions, etc.:




	const Date first_date(1601, Date::January, 1);	// don't try dates anywhere near this far back in time
												// the calendar calculation code is brittle the first date
												// must be the first day of a year divisible by 400
	const Day first_day = monday;				//Januaray 1, 1600 would have been a Monday (had they had the Georgian calendar)

	const Date& default_date()
	{
		static const Date dd(2001, Date::January, 1); // start of 21st century
		return dd;
	}

	int days_in_month(int y, Date::Month m)
	{
		switch (m) {
		case Date::February:                        // the length of February varies
			return (leapyear(y)) ? 29 : 28;
		case Date::April: case Date::June: case Date::September: case Date::November:
			return 30;
		default:
			return 31;
		}
	}

	bool is_date(int y, Date::Month  m, int d)
	{
		// assume that y is valid

		if (d <= 0) return false;            // d must be positive
		if (days_in_month(y, m) < d) return false;

		return true;
	}


	bool leapyear(int y)
	{
		// See exercise 9-10	

		// any year divisible by 4 except centenary years not divisible by 400

		if (y % 4) return false;
		if (y % 100 == 0 && y % 400) return false;
		return true;
	}


	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}


	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}



	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day()
			<< ')';
	}


	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // oops: format error
			is.clear(ios_base::failbit);                    // set the fail bit
			return is;
		}
		dd = Date(y, Date::Month(m), d);     // update dd
		return is;
	}

	int nmonth(int m)
		// number of days before the first day of month #m (january is #1) ignoring leap days
	{
		switch (m)
		{
		case Date::January:	return 0;
		case Date::February:	return 31;
		case Date::March:	return 31 + 28;
		case Date::April:	return 31 + 28 + 31;
		case Date::May:	return 31 + 28 + 31 + 30;
		case Date::June:	return 31 + 28 + 31 + 30 + 31;
		case Date::July:	return 31 + 28 + 31 + 30 + 31 + 30;
		case Date::August:	return 31 + 28 + 31 + 30 + 31 + 30 + 31;
		case Date::September:	return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31;
		case Date::October:	return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
		case Date::November:	return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
		case Date::December:	return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
		}
	}


	int day_in_year(Date a)
		// e.g. Jan 1 is day #1, Jan 2 is day #1 and feb 3 is day #34
	{
		int m = nmonth(a.month());
		if (Date::February < a.month() && leapyear(a.year())) ++m;	// adjust if we passed a dat added for a leapyear
		return m + a.day();
	}


	int nleaps(int y)
		// number of leapyears between Jan 1, y and first_year
		// first_year must be divisible by 400
	{
		const int yy = y - first_date.year();
		return yy / 4 - yy / 100 + yy / 400; // number of leapyears
	}

	int linear_day(Date a)
		// days since default date
	{
		int y = a.year() - first_date.year();
		if (y < 0) error("linear_day: can't handle days before (1601,jan,1)");
		int m = a.month() - first_date.month();
		int d = a.day() - first_date.day();
		/*
			If it wasn't for leap years and different lengths of month the answer would be
				365*y+31*m+d
			However, ther real world (the real physical world + conventions) is not that simple.
		*/
		if (y == 0 && m == 0) return d;	// same month
		int days_in_years = 365 * y + nleaps(a.year());
		return days_in_years + day_in_year(a) - 1;
	}

	Date date_from_linear(int n)
		// compose the Date (2001,jan,1)+n
	{
		return Date(first_date.year(), first_date.month(), first_date.day() + n);	// rather limited implementatiuon :-)
	}

	int operator-(Date a, Date b)
		// how many days are there between a and b?
		// if b is earlier than a the answer will be negative
	{
		int aval = linear_day(a);
		int bval = linear_day(b);
		return aval - bval;
	}


	Date operator+(const Date& d, int dd)
		// dd days beyond d
	{
		Date x = d;
		x.add_day(dd);
		return x;
	}

	/*
		Note the difference between + and - for Date.
		It makes sense to subtract two dates, but not to add two dates
	*/


	Date next_Sunday(const Date& d)
	{
		Day dd = day_of_week(d);
		Date ns = d;
		ns.add_day(7 - dd);
		return ns;
	}


	Date next_weekday(const Date& d)
		// assume that Saturday and Sunday are not weekdays
	{
		Day dd = day_of_week(d);
		int n = 1;
		switch (dd) {
		case friday:	// skip Saturday and Sunday
			n = 3;
			break;
		case saturday:	// Skip Sunday
			n = 2;
			break;
		}
		return d + n;
	}

	int week_in_year(const Date& d)
		// the number of a week in a year is defined by ISO 8601:
		//	week #1 is the week with the year's first Thursday in it
		//	Monday is the first day of the week

		// 0 means that the date is in the last week ofthe previous year
	{
		int diy = day_in_year(d);	// jan 1 is day #1
		Day jan1 = day_of_week(Date(d.year(), Date::January, 1));
		int week1 = 0;	// Jan 1 is in the last week of the previous year
		int delta;
		switch (jan1) {
			// Jan 1 is in the first week of the year
		case monday:
			delta = 0;
			break;
		case tuesday:
			delta = 1;
			break;
		case wednesday:
			delta = 2;
			break;
		case thursday:
			delta = 3;
			break;
			// Jan 1 is in the last week of the previous year
		case friday:
			delta = -3;
			break;
		case saturday:
			delta = -2;
			break;
		case sunday:
			delta = -1;
			break;
		}

		return (diy + delta) / 7;
	}







	ostream& operator<<(ostream& os, const Day& day)
		// sloppy: I should have used a table
	{
		switch (day) {
		case sunday:
			os << "Sunday";
			break;
		case monday:
			os << "Monday";
			break;
		case tuesday:
			os << "Tuesday";
			break;
		case wednesday:
			os << "Wednesday";
			break;
		case thursday:
			os << "Thursday";
			break;
		case friday:
			os << "Friday";
			break;
		case saturday:
			os << "Saturday";
			break;
		}
		return os;
	}

	//****************************Overloading*helpful*functions*********************************//
	


	//****************************************END************************************************//

	int day_interval(const Date& date)						//calculate days between 1-st of January 2020 and 'end'
	{
		const Date start_date{ 1601,Date::Month::January,1 };			//initialize start day
		if (date.year()<1601)
		{
			error("Date mustn't be less than 1601 January 1");
		}
		int y = date.year() - start_date.year();
		//int m = date.month() - start_date.month();
		int nleaps_year = y / 4 - y / 100 + y / 400;
		return y * 365 + nleaps_year + day_in_year(date) - 1;

	}

	Day day_of_week(const Date& date)						//find day of week of 'date'
	{
		Day result;
		return Day((day_interval(date)+int(first_day))% 7);
	}

	bool workday(const Date& date)							//true if weekday of date is Monday, Tuesday... and false if it is Saturday and Sunday
	{
		switch (day_of_week(date))
		{
		case monday: case tuesday: case wednesday: case thursday: case friday:
			return true;
		case saturday: case sunday:
			return false;
		default:
			error("Wrong day of week");
		}
	}
}