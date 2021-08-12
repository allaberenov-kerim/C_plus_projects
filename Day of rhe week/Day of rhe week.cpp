#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"
#include <iostream>
vector<string> days_of_the_week = { "Monday", "Tuesday", "Wednesday",
                                        "Thursday", "Friday", "Saturday",
                                                                "Sunday" };
vector<string> days_of_the_week_con = { "Mon", "Tue", "Wed",
                                    "Thu", "Fri", "Sat", "Sun" };
vector<string> days_of_the_week_small = { "monday", "tuesday", "wednesday",
                                    "thursday", "friday", "saturday",
                                                            "sunday" };
vector<int> values(days_of_the_week.size());

int controller(string days_name)        //control input name (give zero if it rigth and throw error if wrong)
{
    for (int i = 0; i < days_of_the_week.size(); i++)
    {
        if ((days_name == days_of_the_week[i]) || (days_name == days_of_the_week_con[i]) || (days_name == days_of_the_week_small[i]))
        {
            return 0;
        }
    }
    return 1;
}
int summ_counter() // count summ of elements of vector
{
    int summ = 0;
    for (int l = 0; l < values.size(); l++)
    {
        summ += values[l];
    }
    return summ;
}
int main()
{
    while (2 > 0)
    {
        int b = 0;

        string a;
        for (int i = 0; i <values.size(); )
        {

                cin >> a >> b;
            if (controller(a) == 0)
            {
                values[i] = b;
                i++;
            }
            else
            {
                cout << "This value will been ignored as it is wrong\n";
            }
        }
        cout << summ_counter();

    }
}
