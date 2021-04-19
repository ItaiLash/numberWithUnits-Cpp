#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace ariel {

    class NumberWithUnits{

    private:
        double quantity;
        string unit;

    public:
        NumberWithUnits(double quantity, string unit){
            this->quantity = quantity;
            this->unit = unit;
        }
        ~NumberWithUnits(){}
        static void read_units(ifstream& file);
        friend int compare(const NumberWithUnits& obj1, const NumberWithUnits& obj2);

        /* Overloading in/out stream operators */
        friend ostream& operator<<(ostream& out, const NumberWithUnits& num);
        friend istream& operator>>(istream& in, NumberWithUnits& num);

        /* Overloading arithmetic operators */
        friend NumberWithUnits operator+(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend NumberWithUnits operator+(const NumberWithUnits& num);
        friend NumberWithUnits operator+=(NumberWithUnits& num1, const NumberWithUnits& num2);
        friend NumberWithUnits operator-(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend NumberWithUnits operator-(const NumberWithUnits& num);
        friend NumberWithUnits operator-=(NumberWithUnits& num1, const NumberWithUnits& num2);

        /* Overiding increase/decrease operators */
        friend NumberWithUnits operator++(NumberWithUnits& num);       //prefix increment operator
        friend NumberWithUnits operator++(NumberWithUnits& num, int);   //postfix increment operator
        friend NumberWithUnits operator--(NumberWithUnits& num);        //prefix increment operator
        friend NumberWithUnits operator--(NumberWithUnits& num, int);   //postfix increment operator

        /* Overiding multiplication operators */
        friend NumberWithUnits operator*(NumberWithUnits& num, double d);
        friend NumberWithUnits operator*(double d, NumberWithUnits& num);
        friend NumberWithUnits operator*=(NumberWithUnits& num, double d);
        friend NumberWithUnits operator*=(double d, NumberWithUnits& num);

        /* Overloading comparison operators */
        friend bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2);
    };
}