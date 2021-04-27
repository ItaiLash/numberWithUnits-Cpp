#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <limits>
#include "NumberWithUnits.hpp"
using namespace std;
const double EPS = 0.001;

namespace ariel {
    static map<string, map<string, double> > units_table;

    NumberWithUnits::NumberWithUnits(double quantity, const string& unit){
        if(units_table.count(unit) == 0){
            throw invalid_argument{"Unit doesn't exist in the units table!"};
        }
        this->quantity = quantity;
        this->unit = unit;
    }

    void NumberWithUnits::read_units(ifstream& file){
        string buff;
        string unit1;
        string unit2;
        double quantity1 = 0;
        double quantity2 = 0;
        while(file >> quantity1 >> unit1 >> buff >> quantity2 >> unit2) {
            units_table[unit1][unit2] = quantity2;
            units_table[unit2][unit1] = 1/quantity2;

            /* Update unit2 adjencies */
            for(auto &pair : units_table[unit2]) {
                double w = units_table[unit1][unit2] * pair.second;
                units_table[unit1][pair.first] = w;
                units_table[pair.first][unit1] = 1/w;
            }
            /* Update unit1 adjencies */
            for(auto &pair : units_table[unit1]) {
                double w = units_table[unit2][unit1] * pair.second;
                units_table[unit2][pair.first] = w;
                units_table[pair.first][unit2] = 1/w;
            }
        }
    }

    double convertFromTo(double val, const string& from, const string& to){
        if(from == to) {
            return val;
        }
        try {
            return val * units_table.at(from).at(to);
        }
        catch(const exception& e) {
            throw invalid_argument{"Units do not match - ["+from+"] cannot be converted to ["+to+"]"};
        }
    }

    int compare(const NumberWithUnits& obj1, const NumberWithUnits& obj2){
        double obj2_new_quantity = convertFromTo(obj2.quantity, obj2.unit, obj1.unit);
        double compare = obj1.quantity - obj2_new_quantity;
        int ans = 0;
        if(compare > EPS){
             ans = 1;
        }
        else if(compare < -EPS){
            ans = -1;
        }
        return ans;
    }

    // Overloading arithmetic operators 
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& num){
        double num_new_quantity = convertFromTo(num.quantity, num.unit, this->unit);
        NumberWithUnits ans(this->quantity+num_new_quantity, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator+(){
        NumberWithUnits ans(+this->quantity, this->unit);
        return ans;
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& num){    
        this->quantity += convertFromTo(num.quantity, num.unit, this->unit);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& num){
        double num_new_quantity = convertFromTo(num.quantity, num.unit, this->unit);
        NumberWithUnits ans(this->quantity-num_new_quantity, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator-(){
        NumberWithUnits ans(-this->quantity, this->unit);
        return ans;
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& num){
        this->quantity -= convertFromTo(num.quantity, num.unit, this->unit);
        return *this;
    }

    // Overiding increase/decrease operators 
    NumberWithUnits& NumberWithUnits::operator++(){
        (this->quantity)++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int){
        NumberWithUnits copy = *this;
        this->quantity++;
        return copy;
    }
    NumberWithUnits& NumberWithUnits::operator--(){
        (this->quantity)--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits copy = *this;
        this->quantity--;
        return copy;  
    }
    // Overiding multiplication operators 
    NumberWithUnits NumberWithUnits::operator*(double d) const{
        NumberWithUnits ans(this->quantity*d, this->unit);
        return ans;
    }
   
    NumberWithUnits& NumberWithUnits::operator*=(double d){
        this->quantity *= d;
        return *this;
    }

    // Overloading comparison operators
    bool NumberWithUnits::operator>(const NumberWithUnits& num) const{
        return compare(*this, num) > 0;
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits& num) const{
        return compare(*this, num) >= 0;
    }
    bool NumberWithUnits::operator<(const NumberWithUnits& num) const{
        return compare(*this, num) < 0;
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits& num) const{
                return compare(*this, num) <= 0;
    }
    bool NumberWithUnits::operator==(const NumberWithUnits& num) const{
        return compare(*this, num) == 0;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits& num) const{
        return compare(*this, num) != 0;
    }

    // Overloading in/out stream operators 
    ostream& operator<<(ostream& out, const NumberWithUnits& num){
        out << num.quantity << "[" << num.unit << "]";
        return out;
    }

    istream& operator>>(istream& in, NumberWithUnits& num){
        double n = 0;
        string inp_t;
        char suff = ']';
        in >> n;
        in >> suff;
        while (suff != ']') {
            if (suff != '[') {
                inp_t.push_back(suff);
            }
            in>>suff;
        }
        if (units_table.find(inp_t) != units_table.end()) {
            num.quantity = n;
            num.unit = inp_t;
        }
        else {
            throw std::invalid_argument{"There is no such unit in the units file"};
        }
        return in;
    }
}