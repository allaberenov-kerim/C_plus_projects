#include <iostream>
#include <std_lib_facilities.h>;
#include "Chrono.h"
using namespace std;

//=====================================****************===============================//
                                        //Helper class
struct ISBN_type     
{
    ISBN_type(int f, int s, int th, char F);
    ISBN_type();
    //i-i-i-n form where n is digit or literal
    int first_part;         //int-part where i integer
    int second_part;        //int-part where i integer
    int third_part;         //int-part where i integer
    char Fourth_part;       //n-part where n digit or literal
};

ISBN_type::ISBN_type(int f, int s, int th, char F) :first_part{ f }, second_part{ s }, third_part{ th }, Fourth_part{ F }
{
    if (f < 0 && s < 0, th < 0 && F == ' ') error("Wrong ISBN input");
}

ISBN_type::ISBN_type()
{
    ISBN_type data{ 0,0,0,'A' };                                //ISBN default constructor
}

vector<string> genre_table { "fiction","nonfiction","periodical","biography","children" };
enum Genre
{
    fiction = 1, nonfiction, periodical, biography, children
};




//====================================*******************============================//
class Book
{
public:
    Book(string titl, string auth, Genre gnr, ISBN_type code, Chrono::Date copr, bool iss);
    Book();

    ISBN_type ISBN;
    string title;
    string author;
    Genre genre;
    Chrono::Date copyright_date;


    bool issued;                                          //is this book in library yet
    bool is_issued(Book& book);                           //return true if book issued

                  //helper function to check data-member of Book
    bool data_valid();

    bool ISBN_valid();            //return true if ISBN valid
    bool title_valid();              //return true if title valid
    bool author_valid();             //return true if author valid
    bool copyright_date_valid();     //return true if copyright_date valid
};


Book::Book(string titl, string auth, Genre gnr, ISBN_type code, Chrono::Date copr, bool iss) :title{titl}, author{auth},                //constructor for Book
                                                                                        genre(gnr), ISBN{code}, 
                                                                                        copyright_date{copr}, issued{iss}
{
    if (!data_valid())
        error("Wrong input data");
}

Book::Book()
{
    Book book{ "","",Genre::fiction,ISBN_type{0,0,0,'q'},Chrono::Date{2000,Chrono::Date::Month::apr,1},false };
}



bool Book::is_issued(Book& book)        //check whether the book checked out or in
{
    if (book.issued) return true;
}

bool Book::data_valid()                 //get false if input data are wrong
{
    if (!ISBN_valid() || !title_valid() || !author_valid() || !copyright_date_valid())
        return false;
    return true;
}

bool Book::ISBN_valid()                   //get false if ISBN wrong
{
    if (ISBN.first_part< 0 || ISBN.second_part < 0 || ISBN.third_part < 0)           
        return false;
    if (!isalpha(ISBN.Fourth_part) && !isdigit(ISBN.Fourth_part)&&ISBN.Fourth_part==' ')
        return false;
}

bool Book::title_valid()
{
    for (int i = 0; i < title.size(); i++)                        //get to each symbol of author name
    {
        if (!isalpha(title[i]) && title[i] != ' ')               //true if there any digits and another symbols in author name
        {
            return false;                                         //get false if title name is invalid
        }
    }
}

bool Book::author_valid()
{
    for (int i = 0; i < author.size(); i++)                        //get to each symbol of author name
    {
        if (!isalpha(author[i])&&author[i]!=' ')                  //true if there any digits and another symbols in author name
        {
            return false;                                          //get error if author name is invalid
        }
    }
}

bool Book::copyright_date_valid()
{
    if (copyright_date.Chrono::Date::day() < 1 || copyright_date.Chrono::Date::day() > 31) return false;                  //range of days from 1 to 31
    if (copyright_date.Chrono::Date::month() < 1 || copyright_date.Chrono::Date::month() >12) return false;               //range of months from 1 to 12 
    if (copyright_date.Chrono::Date::year() < 1800 || copyright_date.Chrono::Date::year()>2200) return false;             //range of years from 1800 to 2200
}

//====================================*******************==================================//


class Patron {
public:
    Patron(string n, int c_n, double u_f);
    Patron();						//default constructor for each new undefined user

    string user_name;				//name of user
    int card_number;				//number of library card
    double user_fee;				//library fees of user
    bool is_owe;                    //true if user owe

    double set_fee(double&);				//set fee of user
    bool owe_fee(double&);				//check whether user has owe fee or not
};
Patron::Patron(string u_n, int c_n, double u_f) :user_name{ u_n }, card_number{ c_n }, user_fee{ set_fee(u_f) }, is_owe{ owe_fee(u_f) }{if (c_n < 0) error("Wrong card number of ",user_name); };   //Construct Patron{u_n,c_n,u_f}
Patron::Patron()					//definition of default constructor
{					//Name=		card number=0			user fee=0
    user_name = "";
    card_number = 0;
    user_fee = 0;
}

double Patron::set_fee(double& amount)			//set fee to user
{
    if (amount < 0) error("fee cannot be less than zero");
    return amount;
}

bool Patron::owe_fee(double& amount)			//true if there are any owe fees in user owe
{
    if (amount == 0)
        return false;
    if (amount < 0) error("Wrong fee input of ",user_name);
    if (amount > 0) return true;
}

struct Transuction
{
    Transuction(const Patron& p, const Book& b,const Chrono::Date d) :patron{ p }, book{ b }, day{ d } {};

    Patron patron;
    Book book;
    Chrono::Date day{};
};




///******************************HELPER*FUNCTIONS*************************************//


bool operator==(const Book& d1, const Book& d2)
{
    return (d1.ISBN.first_part == d2.ISBN.first_part) && (d1.ISBN.second_part == d2.ISBN.second_part) && (d1.ISBN.third_part == d2.ISBN.third_part) && (d1.ISBN.Fourth_part == d2.ISBN.Fourth_part)&&
        d1.title==d2.title&&d1.author==d2.author&&d1.genre==d2.genre&&d1.copyright_date==d2.copyright_date&&d1.issued==d2.issued;
}

bool operator!=(const Book& d1, const Book& d2)
{
    return (d1.ISBN.first_part != d2.ISBN.first_part) && (d1.ISBN.second_part != d2.ISBN.second_part) && (d1.ISBN.third_part != d2.ISBN.third_part) && (d1.ISBN.Fourth_part != d2.ISBN.Fourth_part);
}        

bool operator==(const Patron& p1, const Patron& p2)
{
    return (p1.user_name == p2.user_name) && (p1.card_number== p2.card_number) && (p1.user_fee== p2.user_fee);
}

bool operator!=(const Patron& p1, const Patron& p2)
{
    return  (p1.user_name == p2.user_name) && (p1.card_number == p2.card_number) && (p1.user_fee == p2.user_fee);
}

ostream& operator<<(ostream& is, Book book)
{
    string available = "Yes";
    if (book.issued)
        available = "No";
    return is << "Title: " << book.title << '\n' << "Author: " << book.author << '\n' << "Genre: " << genre_table[book.genre] << '\n' << "ISBN: " << book.ISBN.first_part << "-" << book.ISBN.second_part << "-" << book.ISBN.third_part << "-" << book.ISBN.Fourth_part << '\n' << "Available: " << available << '\n';
}

ostream& operator<<(ostream& is, Patron patron)
{
    return is << "Client name: " << patron.user_name << '\n' << "Client card number: " << patron.card_number << '\n' << "Client debts " << patron.user_fee << '\n';
}

//******************************HELPER*FUNCTIONS*END**********************************//



/*====================================================================================*/
/*                                  MAIN CLASS LIBRARY                                */
class Library
{
public:
    Library(vector<Patron>&, vector<Book>&, vector<Transuction>&);                      //constructor for Library class
    Library();                                                                          //default constructor for Library class

    vector<Patron> clients;
    vector<Book> books;
    vector<Transuction> Transuctions;

    void add_book(const Book&);
    void add_patron(const Patron&);
    bool checked_out(const Book&);

    void  trans_data(const Patron&, Book&);                                       //do transaction if all data are true and they are in library

    void transaction(const Patron&,Book&);

};
Library::Library(vector<Patron>& p, vector<Book>& b, vector<Transuction>& t) :clients(p), books(b), Transuctions(t) {};
Library::Library()
{
    Library lib{ clients,books,Transuctions };
}

void Library::add_book(const Book& book)                                //add book to the library
{
    books.push_back(book);
}                   

void Library::add_patron(const Patron& patron)                         //add patron to the clients list
{
    clients.push_back(patron);
}           

bool Library::checked_out(const Book& book)
{
    if (!book.issued)
        return false;
}



void Library::trans_data(const Patron& patron, Book& book)
{
    bool has_client = false,
         has_book=false;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i] == patron) has_client = true;
    }
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i] == book) has_book = true;
    }
    if (!has_client) error("There is not such client in list of clients as ",patron.user_name);
    if (!has_book) error("There is not such book in library as ", book.title);
    if (patron.user_fee) error("Patron has fee owes");
    transaction(patron, book);

}

void Library::transaction(const Patron& patron, Book& book)
{
    Chrono::Date d;
    Transuction trans{ patron, book,d };
    if (!book.issued)
    {
        Transuctions.push_back(trans);
        book.issued = true;
    }
    else
        error(book.title, " was issued from the library");

}


int main()
try
{
    ISBN_type ISBN{ 12,34,5,'G' };
    ISBN_type ISBN2{ 01,23,45,'A' };
    Book MyBook1{ "Physic","Myakishev",Genre{periodical},ISBN2,Chrono::Date{2005,Chrono::Date::Month::feb,20},false};
    Book MyBook2{ "Love and peace","Alexandr Sergeyevich Pushkin",Genre::nonfiction, ISBN,Chrono::Date{2003,Chrono::Date::Month::apr,20},false };

    Patron Client1{"Kerim",12,0};
    Patron Client2{ "Ahmet", 16,0 };
    
    Library lib;
    lib.add_patron(Client1);
    lib.add_patron(Client2);
    lib.add_book(MyBook2); lib.add_book(MyBook1);
    lib.trans_data(Client1, MyBook2);
    lib.trans_data(Client2, MyBook1);
    cout << "Transaction has successfully ended";
}
catch (exception& e)
{
    cout << e.what();
}


