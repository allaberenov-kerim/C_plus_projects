#include <iostream>
#include "std_lib_facilities.h"
#include "Chrono.h"
using namespace Chrono;

int main()
try
{
	Date MyBirth{ 2003,Date::Month::May,21 };
	Date AhmetBirth{ 2011,Date::Month::December,10 };

	Date end_time{1600,Date::December,16};
	cout<<day_of_week(end_time)<<'\n';

	if (Chrono::workday(end_time))
		cout << "Workday";
	else
		cout << "Not workday";
}
catch (exception& e)
{
	cout << e.what();
}