#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace ariel{

    class NumberWithUnits{

    private:
        double quantity;
        string unit;

    public:
        NumberWithUnits(double quantity, const string& unit);
        ~NumberWithUnits(){}
        static void read_units(ifstream& file);
        friend int compareTo(const NumberWithUnits& obj1, const NumberWithUnits& obj2);

        // Overloading arithmetic operators
        NumberWithUnits operator+(const NumberWithUnits& num);
        NumberWithUnits operator+();
        NumberWithUnits& operator+=(const NumberWithUnits& num);
        NumberWithUnits operator-(const NumberWithUnits& num);
        NumberWithUnits operator-();
        NumberWithUnits& operator-=(const NumberWithUnits& num);

        // Overiding increase/decrease operators 
        NumberWithUnits& operator++();        // prefix increment operator
        NumberWithUnits operator++(int);      // postfix increment operator
        NumberWithUnits& operator--();        // prefix increment operator
        NumberWithUnits operator--(int);      // postfix increment operator

        // Overiding multiplication operators 
        NumberWithUnits operator*(double d) const;
        NumberWithUnits& operator*=(double d);
        friend NumberWithUnits operator*(double d, const NumberWithUnits& num){
            return num*d;
        }

        // Overloading comparison operators 
        bool operator>(const NumberWithUnits& num) const;
        bool operator>=(const NumberWithUnits& num) const;
        bool operator<(const NumberWithUnits& num) const;
        bool operator<=(const NumberWithUnits& num) const;
        bool operator==(const NumberWithUnits& num) const;
        bool operator!=(const NumberWithUnits& num) const;


        // Overloading in/out stream operators 
        friend ostream& operator<<(ostream& out, const NumberWithUnits& num);
        friend istream& operator>>(istream& in, NumberWithUnits& num);
    };
}