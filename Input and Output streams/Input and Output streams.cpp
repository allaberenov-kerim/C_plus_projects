#include <std_lib_facilities.h>
#include <iostream>

/*struct Reading								//data type
{
	int hour;
	double temperature;
};

void fill_vector(istream& ist, vector<int>& v, char terminator)
{
	for (int i; ist >> i;) v.push_back(i);
	if (ist.eof()) return;
	if (ist.bad()) error("Bad occoured");
	if (ist.fail()) {
		ist.clear();

		char c;
		ist >> c; // read a character, hopefully terminator
		if (c != terminator) { // unexpected character
			ist.unget(); // put that character back
			ist.clear(ios_base::failbit);
		}
	}

}

int main()
try
{
	cout << "Please enter input file name: ";
	string iname;
	cin >> iname;
	ifstream ist{ iname }; // ist reads from the file named iname
	if (!ist) error("can't open input file ", iname);

	string oname;
	cout << "Please enter name of output file: ";
	cin >> oname;
	ofstream ost{ oname }; // ost writes to a file named oname
	if (!ost) error("can't open output file ", oname);

	vector<Reading> temps; // store the readings here
	int hour;
	double temperature;
	while (ist >> hour >> temperature) {
		if (hour < 0 || 23 < hour) error("hour out of range");
		temps.push_back(Reading{ hour,temperature });
	}

	vector<int> hours;
	int hour;
	while (ist >> hour) fill_vector(ist, hours, '*');

	if (ist.fail()) error("ist was failed");

	/*for (int i = 0; i < temps.size(); i++)
	{
		ost << '(' << temps[i].hour << ',' << temps[i].temperature << ")\n";
	}
}*/


void skip_to_int()								//skip all symbols until find int
{
	if (cin.fail()) {
		cin.clear();
		for (char ch; cin >> ch;)
		{
			if (isdigit(ch))
			{
				cin.unget();
				return;
			}
		}
	}
}		

int get_int()										//get int from istream
{
	int n;
	while (cin)
	{
		if (cin >> n) return n;
		cout << "Sorry, please input int number";
		skip_to_int();
	}
}

int get_int(int low, int high, const string& greeting, const string& sorry)		//get int from istream with ranges from 'low' to 'high'
{
	cout << greeting
		<< low << " to " << high << " (inclusive):\n";
	while (true)
	{
		int a = get_int();
		if (a >= low && a <= high)
			return a;
		else
			cout << sorry
			<< "[" << low << ':' << high
			<< "] \n";
	}
}

void end_of_loop(istream& is, const char& term, const string& message)						//return end of loop if it sees 'term' and it isn't any error in input stream
{
	if (is.fail())
	{
		char ch;
		is.clear();
		if (is >> ch && term == term) return;
		error(message);
	}
}

//**************************************************************************************

const int not_a_reading = -7777;				//hours which aren't initialized (less than absolute zero)
const int not_a_month = -1;						//months which aren't initialized (less than absolute zero)


struct Day {
	vector<double> hour=vector<double>(24, not_a_reading);
};

struct Month {						// a month of temperature readings
	int month{not_a_month};
	vector<Day> day{ 32 };
};

struct Year
{
	int year;
	vector<Month> month{ 12 };			  // [0:11] January is 0
};

struct Reading
{
	int day;
	int hour;
	double temperature;
};


constexpr int implausible_max = 200;
constexpr int implausible_min = -200;
bool is_valid(const Reading& r)
{
	if (r.day < 1 || r.day > 31) return false;
	if (r.hour < 0 || r.hour>23) return false;
	if (r.temperature<implausible_min || r.temperature>implausible_max) return false;
	return true;
}


vector<string> month_input_tbl = {
"jan", "feb", "mar", "apr", "may", "jun", "jul",
"aug", "sep", "oct", "nov", "dec"
};
int month_to_int(string s)
// is s the name of a month? If so return its index [0:11] otherwise –1
{
	for (int i = 0; i < 12; ++i) if (month_input_tbl[i] == s) return i;
	return -1;
}



vector<string> month_print_tbl = {
"January", "February", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December"
};
string int_to_month(int i)
// months [0:11]
{
	if (i < 0 || 12 <= i) error("bad month index");
	return month_print_tbl[i];
}



istream& operator>>(istream& is, Reading& r)				//read 'Reading'-type from 'is'-input stream
{
	char ch1;
	if (is>>ch1&&ch1!='(') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') error("Bad input");
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}


istream& operator>>(istream& is, Month& m)
{
	char ch=0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string month_marker;			//start month's name with month's marker (month jun)
	string mn;						//month name
	is >> month_marker >> mn;
	if (!is || month_marker != "month") error("Bad input");

	m.month = month_to_int(mn);
	int duplicate=0;
	int invalids = 0;
	for (Reading r; is >> r;)
	{
		if (is_valid(r))
		{
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicate;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
			++invalids;
	}
	if (invalids) error("invalid readings in month", invalids);
	if (duplicate) error("duplicate readings in month", duplicate);
	end_of_loop(is, '}', "bad end of month");
	return is;
}


istream& operator>>(istream& is, Year& y)
{
	char ch;
	is >> ch;
	if (ch!='{')
	{
		is.clear(ios_base::failbit);
		is.unget();
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is||year_marker!="year") error("bad start of year");
	y.year = yy;
	while (true) {
		Month m; // get a clean m each time around
		if (!(is >> m)) break;
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}
/*
ostream& operator<<(ostream& os, vector<double>& hour)
{
	for (int i = 0; i < hour.size(); i++)
	{
		if (hour[i] != -7777)	os << i << "	" << hour[i] << '\n' << "			";
	}
	return os;
}

ostream& operator<<(ostream& os, vector<Day>& day)
{
	for (int k = 0; k < day.size(); k++)
	{
		os << k <<"	" << day[k].hour <<'\n'<< "		";
	}
	return os;
}

ostream& operator<<(ostream& os, vector<Month>& month)
{
	for (int i = 0; i < month.size() - 1; i++)
	{
		if (month[i].month != -1)
			os << "	" << int_to_month(month[i].month) << '\n' << "		" << month[i].day << '\n';
	}
	return os;
}
*/


void print_year(ostream& ofs, Year& y)
{
	ofs << y.year << '\n';
	for (Month& m:y.month)
	{
		if (m.month != not_a_month) {
			ofs << '\t' << int_to_month(m.month) << '\n';
			
			for (int d = 1; d < m.day.size(); d++)
			{
				for (int h = 0; h < m.day[d].hour.size(); h++)
				{
					if (m.day[d].hour[h]!=not_a_reading)
					{
						ofs << "\t\t" << d << '\t' << h << '\t' << m.day[d].hour[h] << '\n';
					}
				}
			}
		}
	}
	/* {
		cout<<"		"<< int_to_month(y.month[i].month)<<'\n';
		for (int k = 0; k < y.month[i].day.size(); k++)
		{
			cout << y.month[i].day[k] << "	";
			for (int l = 0; l < y.month[i].day[k].hour.size(); l++)
			{
				cout<<y.month[i].day[k].hol]<<"	" << y.month[i].day[k].hour[l] '\n';
			}
		}
	}*/
}



int main()
try
{
	// open an input file:
	cout << "Please enter input file name\n";
	string iname;
	//cin >> iname;
	ifstream ist{ "input.txt"};
	if (!ist) error("can't open input file ", iname);
	ist.exceptions(ist.exceptions() | ios_base::badbit); // throw for bad()
	// open an output file:
	cout << "Please enter output file name\n";
	string oname;
	//cin >> oname;
	ofstream ost{ "output.txt" };
	if (!ost) error("can't open output file ", oname);
	// read an arbitrary number of years:
	vector<Year> ys;
	while (true) {
		Year y; // get a freshly initialized Year each time around
		if (!(ist >> y)) break;
		ys.push_back(y);
	}
	cout << "read " << ys.size() << " years of readings\n";

	for (Year& y : ys) print_year(ost, y);
}
	catch (exception& e)
{
	cout << e.what();
}