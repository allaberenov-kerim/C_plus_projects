#include <std_lib_facilities.h>
namespace Chrono {


    //------------------------------------------------------------------------------
   
    class Date {
    public:
        
        enum Month {
            January = 1, February, March, April, May, June, July, August, September, October, November, December
        };

        class Invalid { };                 // to throw as exception

        Date(int y, Month m, int d);       // check for valid date and initialize
        Date();                            // default constructor
        // the default copy operations are fine

        // non-modifying operations:
        int   day()   const { return d; }
        Month month() const { return m; }
        int   year()  const { return y; }

        // modifying operations:
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
    private:
        int   y;
        Month m;
        int   d;
    };


    bool is_date(int y, Date::Month m, int d); // true for valid date

    bool leapyear(int y);                  // true if y is a leap year

    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);

    ostream& operator<<(ostream& os, const Date& d);
    istream& operator>>(istream& is, Date& dd);

    const Date& default_date();

	int nmonth(int m);


    int day_in_year(Date a);


        int nleaps(int y);

        int linear_day(Date a);

        Date date_from_linear(int n);


        Date operator+(const Date& d, int dd);

        
        enum Day {	// sunday==0
            sunday=0, monday, tuesday, wednesday, thursday, friday, saturday
        };



        Date next_Sunday(const Date& d);


        Date next_weekday(const Date& d);

        int week_in_year(const Date& d);


        //************************************************************************************
  
       ostream& operator<<(ostream& os, const Day& day);

        int day_interval(const Chrono::Date& end);

        Day day_of_week(const Date& date);

        bool workday(const Date& date);

} // Chrono
 
