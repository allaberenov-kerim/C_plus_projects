/*
    Simple calculator


    This program implements a basic expression calculator.
    Input from cin; output to cout.

    The grammar for input is:

    Calculation:
        Statement
        Print
        Quit
        Calculation Statement

    Statement:
        Declaration
        Expression

    Declaration:
        "let" Name "=" Expression
        "let" "const" Name "=" Expression

    Print:
        ;

    Quit:
        q

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        Name
        Name = Expression
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal
    Name:
        [a-zA-Z][a-zA-Z_0-9]*	// a letter followed by zero or more letters, underscores, and digits
                                // note that I decided not to start a namewith an underscore
                                // just because I consider it ugly)

        Input comes from cin through the Token_stream called ts.
*/

#include<iostream>
#include "C:\Users\user\source\repos\Hello, Wordl!\Hello, Wordl!/std_lib_facilities.h"

//-----------------------------------------------------------------------------------------

const char number = '8';
const char quit = '~';
const char print = ';';
const char comma = ',';     //used in pow(... , ...) funct
const std::string prompt = "> ";
const std::string result = "= ";
const char name = 'a';
const char let = 'L';
const char sqr = 'S';
const char pwr = 'P';
const char con = 'C';
const string sqrtkey = "sqrt";
const string powkey = "pow";
const string quitkey = "quit";
const string declkey = "let";
const string constkey = "const";
const string helpkey = "help";

void help_inst()
{
    cout << "Welcome to calculator program!";
    cout << "\nThis program can operate with integer,floating-point numbers, and with variables. It handles such ariphmetic operators such as '+, -, *, /, %, sqrt(...){square root}, pow(*,*)'."
        << " Before using variable, it must was declared earlier with <let> operator.\n"
        << "			<expr>/<...> - is an expression\n"
        << "			<*> - is an integer number\n\n\n";
    cout << "There are operators this program can handle:\n\n";
    cout << "  let const <variable_name>'='<expr>	--to declare new constant variable		{Exp:let const x = 1 * 2}\n" <<
        "					  with appropriately value\n";
    cout << "  let <variable_name>'='<expr>		--to declare new variable			{Exp:let x=1*2}\n" <<
        "					  with appropriately value\n";
    cout << "  <variable_name>'='<expr>		--to assing non-constant variable 		{Exp:x=1*2}\n" <<
        "					  with appropriately value\n";
    cout << "  <expr>(<new_line> or ';')		--to solve an expression 			{Exp:5+6<new_line> or x+6;}\n\n" <<
        "				Rule for variable's name\n" <<
        " Names can be:\n" <<
        "[a - zA - Z][a - zA - Z_0 - 9] *	a letter followed by zero or more letters, underscores, and digits" <<
        "								note that I decided not to start a namewith an underscore\n\n";
}
void calculate();
//-------------------------------------------------------------
class Token
{
public:
    char kind;
    double value;
    string name;
    Token(char ch)
        :kind(ch), value(0) {}
    Token(char ch, double val)
        :kind(ch), value(val) {}
    Token(char ch, string n) :kind(ch), name(n) {};
};
//-------------------------------------------------------------
//-------------------------------------------------------------
class Token_stream
{
public:
    Token_stream();
    Token get();
    void putback(Token t);
    void ignore(char ch);
//    istream& qwerty;
private:
    bool full;
    Token buffer;
};
Token_stream ts;


Token_stream::Token_stream()
    :full(false), buffer(0) {}
void Token_stream::ignore(char ch)
{
    if (full && ch == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;
    char c;
    cin.get(c);
   
    while (isspace(c))
    {
            return;
    }
}
void Token_stream::putback(Token t)
{
    if (full)
        throw std::runtime_error("putback() into a full buffer");
    buffer = t;
    full = true;
}
Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }
    
    char ch;
    cin.get(ch);
    if (isspace(ch))
    {
        if (ch == '\n')
            return Token(print);
    }
    cin.putback(ch);
    cin >> ch;
    
    switch (ch)
    {
    case print: //    case quit:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
    case ',':
    case let:
        return Token(ch);
        break;
    case'.':
    case'0': case'1': case'2': case'3': case'4':
    case'5': case'6': case'7': case'8': case'9':
    {
        cin.putback(ch);
        double val;
        cin >> val;
        return Token(number, val);
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || (ch == '_'))) s += ch;
            cin.putback(ch);
            if (s == quitkey) return Token(quit);
            if (s == declkey)return Token(let);
            if (s == sqrtkey) return Token(sqr);    //return Token('S',0) if is. For sqrt()
            if (s == powkey) return Token(pwr);     //return Token('P',0) if is. For pow()
            if (s == constkey) return Token(con);
            if (s == helpkey) 
            {
                help_inst();
                error("Type in your expression again\n");
            }
            return Token(name, s);
        }
        throw runtime_error("Bad Token");
    }
}

//-------------------------------------------------------------
//-------------------------------------------------------------
class Variable
{
public:
    string name;
    double value;
    bool constant;
    Variable(string s, double d, bool b) :name(s), value(d), constant(b) { }
};
//-------------------------------------------------------------
//-------------------------------------------------------------
class Symbol_table
{
public:
    
    
    bool is_declared(string var);
    double get_value(string s);
    void set_value(string s, double d);
    void define_name(string var, double val, bool constant);
    vector<Variable> var_table;
    
};
Symbol_table s;
    
bool Symbol_table::is_declared(string var) // is var already in var_table?
{
    
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == var) return true;
    return false;
}

void Symbol_table::define_name(string str, double val, bool constant)
{
    if (is_declared(str)) error(str, " declared twice");
    //var_table.push_back(Variable{ var,val,constant });
    
    Variable variable = { str,val,constant };
    var_table.push_back(variable);
}

double Symbol_table::get_value(string str) // return the value of the Variable names s
{
    for (Variable a : var_table)
    {
        if (str == a.name)
        {
            return a.value;
        }
    }
    error("get: undefined variable: ", str);
}
void Symbol_table::set_value(string str, double d) // set the Variable named s with value d
{
    int i = 0;
    for (Variable v : var_table)
    {
        if (v.name == str)
        {
            if (v.constant) error("This is constant variable.");
            var_table[i].value = d;
            return;

        }
        i++;
    }
}

//-------------------------------------------------------------
double primary(Token_stream& ts);
double term(Token_stream& ts);
double expression(Token_stream& ts);
//-------------------------------------------------------------
double Sqrt(Token_stream ts)
{
    Token t1 = ts.get();
    if (t1.kind != '(') error("'(' missing ");
    double d = expression(ts);
    if (d < 0) error("There isn't sense of exression because sqrt() less than 0. ");
    Token t2 = ts.get();
    if (t2.kind != ')') error("')' missing ");
    return sqrt(d);
}
double pow(Token_stream ts)    //Multiply x with itself i times
{
    Token t=ts.get();
    if (t.kind != '(') error("'(' is missing"); //check is '(' at the start 
    Token s = ts.get();        
    double x = s.value;    //get value and assing it to 'x'
    Token t1 = ts.get();
    if (t1.kind != comma) error(" comma(',') is missing");
    Token l = ts.get();
    int i = narrow_cast<int>(l.value);      //get info loss error if ...<...>(double)
    double result=1;
    Token t2 = ts.get();
    if (t2.kind != ')') error(" ')' is missing");
    for ( i; i >=1; i--)
    {
        result *= x;
    }
    return result;

}//------------------------------------------------------------

//-------------------------------------------------------------

double primary(Token_stream& ts)        // handle '(' expression ')'
{
    Token t = ts.get();
    switch (t.kind)
    {
    case'(':    
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')') throw runtime_error("')' expected");
        return d;
    }
    case '-':       //handle -primary
        return -primary(ts);
    case '+':       //handle +primary
        return primary(ts);
    case number:
        return t.value;    // return the number's value
    case name:
    {
        Token next = ts.get();
        if (next.kind == '=') {	// handle name = expression
            double d = expression(ts);
          s.set_value(t.name, d);
            return d;
        }
        else {
            ts.putback(next);		// not an assignment: return the value
            return s.get_value(t.name); // return the variable's value
        }
    }
        return s.get_value(t.name);
    case sqr:
        return Sqrt(ts);
        break;
    case pwr:
        return pow(ts);
        break;

    default:
        throw runtime_error("primary expected!");
    }
}
//------------------------------------------------------------------------
double term(Token_stream& ts)       //handle " * , / , % "
{
    double left = primary(ts);
    Token t = ts.get();
    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary(ts);
            t = ts.get();
            break;
        case '/':
        {
            double d = primary(ts);
            if (d == 0) throw runtime_error("Divide by zero!");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        { 
            int i1 = narrow_cast<int>(left);
            int i2 = narrow_cast<int>(primary(ts));
            if (i2 == 0) error("%: divide by zero");
            left = i1 % i2;
            t = ts.get();
        break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression(Token_stream& ts)     //handle " + , - "
{
    double left = term(ts);
    Token t = ts.get();
    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term(ts);
            t = ts.get();
            break;
        case '-':
            left -= term(ts);
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//-------------------------------------------------------------
void clean_up_mess()
{
    ts.ignore(print);
}
//-------------------------------------------------------------
double declaration()        //delcarate new variable
{
    bool cn_state = false;
    Token t = ts.get();
    if (t.kind == con)      //get con true if it is constant variable
        cn_state = true;
    else
        ts.putback(t);
    Token t1 = ts.get();        //get variable's name=var_name
    if (t1.kind!=name)
        error("name expected in declaration");
    string var_name = t1.name;

    Token t2 = ts.get();        //check is there '=' char
    if (t2.kind != '=')
        error("= missing in declaration of ", var_name);
    double d = expression(ts);
    s.define_name(var_name, d, cn_state);
    return d;
}
//-------------------------------------------------------------
double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
        break;
    default:
        ts.putback(t);
        return expression(ts);
     

    }
}
//-------------------------------------------------------------   
void calculate()
{
    while (true)
    {
        try
        {
            double val = 0;
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)     //ignore all input until it isn't equal ';'
                t = ts.get();
            if (t.kind == quit)
                return;
            ts.putback(t);
            cout << result << statement() << '\n';

        }
        catch (exception& e)
        {
            cout << (e.what()) << '\n';
            clean_up_mess();            
        }
    }
}
//-------------------------------------------------------------

int main()
try
{
    // predefine names:
    s.define_name("pi", 3.1415926535,true);
    s.define_name("e", 2.7182818284,true);
    calculate();
    return 0;

}
catch (exception& e)
{
    cerr << e.what() << '\n';
    clean_up_mess();
    
}
catch (...)
{
    cerr << "exception \n";
    return 2;
}