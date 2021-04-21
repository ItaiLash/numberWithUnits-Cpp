#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel {
    void NumberWithUnits::read_units(ifstream& file){}
    int compare(const NumberWithUnits& obj1, const NumberWithUnits& obj2){
        return 0;
    }

    // Overloading arithmetic operators 
    NumberWithUnits operator+(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return num1;
    }
    NumberWithUnits operator+(const NumberWithUnits& num){
        return num;
    }
    NumberWithUnits operator+=(NumberWithUnits& num1, const NumberWithUnits& num2){    
        return num1;
    }
    NumberWithUnits operator-(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return num1;
    }
    NumberWithUnits operator-(const NumberWithUnits& num){
        return num;
    }
    NumberWithUnits operator-=(NumberWithUnits& num1, const NumberWithUnits& num2){
        return num1;
    }

    // Overiding increase/decrease operators 
    NumberWithUnits operator++(NumberWithUnits& num){
        return num;
    }
    NumberWithUnits operator++(NumberWithUnits& num, int){
        return num;
    }
    NumberWithUnits operator--(NumberWithUnits& num){
        return num;
    }
    NumberWithUnits operator--(NumberWithUnits& num, int){
        return num;
    }
    // Overiding multiplication operators 
    NumberWithUnits operator*(NumberWithUnits& num, double d){
        return num;
    }
    NumberWithUnits operator*(double d, NumberWithUnits& num){
        return num;
    }
    NumberWithUnits operator*=(NumberWithUnits& num, double d){
        return num;
    }
    NumberWithUnits operator*=(double d, NumberWithUnits& num){
        return num;
    }

    // Overloading comparison operators
    bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return true;
    }
    bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return true;
    }
    bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return true;
    }
    bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return true;
    }
    bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return true;
    }
    bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return true;
    }

    // Overloading in/out stream operators 
    ostream& operator<<(ostream& out, const NumberWithUnits& num){
        return out;
    }
    istream& operator>>(istream& in, NumberWithUnits& num){
        return in;
    }
}