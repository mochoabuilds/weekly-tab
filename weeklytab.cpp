// withdraw $ from an account by decreasing acct and
// deposit $ by increasing an acct by overloading compound assignment operators
//
// the value of each these operators will be the
// object to which the operator is applied

// PREPROCESSOR DIRECTIVES
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// CLASS DECLARATIONS
class Savings_Account
{
private:
    char    id_no[5];
    char*   name;
    double  balance;
    double  rate;

    // METHOD DECLARATIONS
public:
    Savings_Account(char id[], char* n_p,
                    double bal = 0.00, double rt = 0.04);

    Savings_Account(const Savings_Account &);
    ~Savings_Account();
    double Calc_Interest();
    double Get_Balance();
    const char* Get_Id() const;
    const char* Get_Name() const;
    Savings_Account& operator += (const double);
    Savings_Account& operator -= (const double);
    Savings_Account& operator = (const Savings_Account&);

    // friend function overloading insertion operator
    friend ostream& operator << (ostream&, const Savings_Account&);
};

Savings_Account::Savings_Account(char id[], char* n_p, double bal, double rt)
{
    strcpy(id_no, id); // copy first argument into id_no[]

    name = new char[strlen(n_p) + 1]; // create space for name

    strcpy(name, n_p); // copy second argument into new space
    balance = bal;
    rate    = rt;
}

Savings_Account::Savings_Account(const Savings_Account& acc_r)
{
    strcpy(id_no, acc_r.id_no); // copy first argument into id_no[]

    name = new char[strlen(acc_r.name) + 1]; // create space for name

    strcpy(name, acc_r.name); // copy second argument into new space

    balance = acc_r.balance;
    rate    = acc_r.rate;
}

Savings_Account::~Savings_Account()
{
    delete [] name;
}

double Savings_Account::Get_Balance()
{
    return balance;
}

double Savings_Account::Calc_Interest()
{
    double interest;
    interest = balance * rate;
    balance += interest;

    return interest;
}

const char* Savings_Account::Get_Name() const
{
    return name;
}

const char* Savings_Account::Get_Id() const
{
    return id_no;
}

Savings_Account& Savings_Account::operator += (const double right_op)
{
    balance += right_op;

    return *this;
}

Savings_Account& Savings_Account::operator -= (const double right_op)
{
    balance -= right_op;

    return *this;
}

Savings_Account& Savings_Account::operator = (const Savings_Account&
right_op)
{
    if(&right_op == this)
        ; // self assignment - do nothing
    else
    {
        strcpy(id_no, right_op.id_no); // copy id of right_op into id_no[]

        delete [] name;

        name = new char[strlen(right_op.name) + 1]; // create space for name

        strcpy(name, right_op.name); // copy second argument into new space

        balance = right_op.balance;
        rate    = right_op.rate;
    }
    return *this;
}

ostream& operator << (ostream& os, const Savings_Account& right_op)
{
    os << endl;
    os << "Data for Account#" << right_op.id_no << endl << endl;

    os << "Owner's Name: " << right_op.name << endl << endl;

    os << "Account Balance: " << right_op.balance << endl;

    return os;
}

Savings_Account Get_Account(); // prototype for Get_Account()

// DEFINITION OF MAIN()
int main()
{
    // helper functions
    cout << setprecision(2)
         << setiosflags(ios::fixed)
         << setiosflags(ios::showpoint);

    double amount;

    Savings_Account acc1 = Get_Account();

    cout << acc1;

    cout << endl;
    cout << "Enter an amount to deposit: ";
    cin >> amount;

    acc1 += amount;

    cout << endl;
    cout << "After the deposit: " << endl << endl << acc1;

    cout << endl;
    cout << "Enter an amount to withdraw: ";
    cin >> amount;

    acc1 -= amount;

    cout << endl;
    cout << "After the withdrawal: " << endl << endl << acc1;

    cout << endl;
    return 0;
}

Savings_Account Get_Account()
{
    char id[5];
    char buffer[81];
    double bal;
    double rt;

    cout << endl;
    cout << "Enter Account ID: ";
    cin.getline(id, 5);

    cout << endl;
    cout << "Enter Account Holder's Name: ";
    cin.getline(buffer, 81);

    cout << endl;
    cout << "Enter Balance: ";
    cin >> bal;

    cout << endl;
    cout << "Enter Interest Rate: ";
    cin >> rt;

    cin.get(); // clear newline character from buffer

    Savings_Account acc(id, buffer, bal, rt);

    return acc;
}
