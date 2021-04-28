#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "NumberWithUnits.hpp"

using namespace std;

const double EPS = 0.001;

namespace ariel {
    static map<string, map<string, double> > units_table;

    /**
     * @brief constructor
     * 
     * @param quantity  
     * @param unit      
     */
    NumberWithUnits::NumberWithUnits(double quantity, const string& unit)
    {
        if(units_table.count(unit) == 0)
        {
            throw invalid_argument{"Unit doesn't exist"};
        }
        this->quantity = quantity;
        this->unit = unit;
    }

    /**
     * @brief Read a text file where each line is in the format:
     * 1 [unit_a] = [quantity] [unit_b]
     * And build a map of units.
     * 
     * @param file a file stream..
     */
    void NumberWithUnits::read_units(ifstream& file)
    {
        string ignore_buffer;
        string unit_a;
        string unit_b;
        double quantity_a = 0;
        double quantity_b = 0;
        double d;

        while(file >> quantity_a >> unit_a >> ignore_buffer >> quantity_b >> unit_b)
        {
            units_table[unit_a][unit_b] = quantity_b;
            units_table[unit_b][unit_a] = 1/quantity_b;

            for(auto &pair : units_table[unit_b])
            {
                d = units_table[unit_a][unit_b] * pair.second;
                units_table[unit_a][pair.first] = d;
                units_table[pair.first][unit_a] = 1/d;
            }

            for(auto &pair : units_table[unit_a])
            {
                d = units_table[unit_b][unit_a] * pair.second;
                units_table[unit_b][pair.first] = d;
                units_table[pair.first][unit_b] = 1/d;
            }
        }
    }

    /**
     * @brief convert the quantity of unit_a to unit_b
     * 
     * @param q       Quantity 
     * @param unit_a  Source unit
     * @param unit_b  destination unit
     * 
     * @return  The quantity after conversion
     */
    double convertUnit(double q, const string& unit_a, const string& unit_b)
    {
        if(unit_a == unit_b)
        {
            return q;
        }
        try 
        {
            return q * units_table.at(unit_a).at(unit_b);
        }
        catch(const exception& err) 
        {
            throw invalid_argument{"["+unit_a+"] cannot be converted to ["+unit_b+"]"};
        }
    }

    /**
     * @brief compare between two NumberWithUnits object.
     * If the units are not comparable an exception will be thrown.
     * 
     * @param obj1  NumberWithUnits object to comapre
     * @param obj2  NumberWithUnits object to comapre
     * 
     * @return 1 if obj1 > obj2, -1 if obj1 < obj2 and 0 if obj1 = obj2
     */
    int compareTo(const NumberWithUnits& obj1, const NumberWithUnits& obj2)
    {
        double obj2_new_quantity = convertUnit(obj2.quantity, obj2.unit, obj1.unit);
        double compare = obj1.quantity - obj2_new_quantity;
        int ans = 0;
        if(compare > EPS){ans = 1;}
        else if(compare < -EPS){ans = -1;}
        return ans;
    }

    // Overloading arithmetic operators 
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& num)
    {
        double num_new_quantity = convertUnit(num.quantity, num.unit, this->unit);
        NumberWithUnits ans(this->quantity+num_new_quantity, this->unit);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        NumberWithUnits ans(+this->quantity, this->unit);
        return ans;
    }

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& num)
    {    
        this->quantity += convertUnit(num.quantity, num.unit, this->unit);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& num)
    {
        double num_new_quantity = convertUnit(num.quantity, num.unit, this->unit);
        NumberWithUnits ans(this->quantity-num_new_quantity, this->unit);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
        NumberWithUnits ans(-this->quantity, this->unit);
        return ans;
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& num)
    {
        this->quantity -= convertUnit(num.quantity, num.unit, this->unit);
        return *this;
    }

    // Overiding increase/decrease operators 
    NumberWithUnits& NumberWithUnits::operator++()
    {
        (this->quantity)++;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits copy = *this;
        this->quantity++;
        return copy;
    }

    NumberWithUnits& NumberWithUnits::operator--()
    {
        (this->quantity)--;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits copy = *this;
        this->quantity--;
        return copy;  
    }

    // Overiding multiplication operators 
    NumberWithUnits NumberWithUnits::operator*(double d) const
    {
        NumberWithUnits ans(this->quantity*d, this->unit);
        return ans;
    }

    NumberWithUnits& NumberWithUnits::operator*=(double d)
    {
        this->quantity *= d;
        return *this;
    }

    // Overloading comparison operators
    bool NumberWithUnits::operator>(const NumberWithUnits& num) const
    {
        return compareTo(*this, num) > 0;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits& num) const
    {
        return compareTo(*this, num) >= 0;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits& num) const
    {
        return compareTo(*this, num) < 0;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits& num) const
    {
                return compareTo(*this, num) <= 0;
    }

    bool NumberWithUnits::operator==(const NumberWithUnits& num) const
    {
        return compareTo(*this, num) == 0;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits& num) const
    {
        return compareTo(*this, num) != 0;
    }

    // Overloading in/out stream operators 
    ostream& operator<<(ostream& out, const NumberWithUnits& num)
    {
        out << num.quantity << "[" << num.unit << "]";
        return out;
    }

    istream& operator>>(istream& in, NumberWithUnits& num)
    {
        double q = 0;
        string u;
        char input = ']';
        in >> q;
        in >> input;
        while (input != ']') 
        {
            if (input != '[') {u.push_back(input);}
            in>>input;
        }
        if (units_table.find(u) != units_table.end()) 
        {
            num.quantity = q;
            num.unit = u;
        }
        else 
        {
            throw std::invalid_argument{"Unit doesn't exist"};
        }
        return in;
    }
}