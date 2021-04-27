#include "doctest.h"
#include "NumberWithUnits.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>

using namespace ariel;
using namespace std;

ifstream units_file{"units.txt"};

TEST_CASE("Binary + and - operator"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits one_km{1, "km"};
    NumberWithUnits three_meters{3, "m"};
    NumberWithUnits five_kg{5, "kg"};
    NumberWithUnits seven_grams{7, "g"};

    CHECK_EQ(one_km + three_meters, NumberWithUnits{1.003, "km"});
    CHECK_EQ(three_meters + one_km, NumberWithUnits{1003, "m"});
    CHECK_EQ(one_km - three_meters, NumberWithUnits{0.997, "km"});
    CHECK_EQ(three_meters - one_km, NumberWithUnits{-997, "m"});

    CHECK_EQ(five_kg + seven_grams, NumberWithUnits{5.007, "kg"});
    CHECK_EQ(seven_grams + five_kg, NumberWithUnits{5007, "g"});
    CHECK_EQ(five_kg - seven_grams, NumberWithUnits{4.993, "kg"});
    CHECK_EQ(seven_grams - five_kg, NumberWithUnits{-4993, "g"});

    CHECK_THROWS(one_km + five_kg);
    CHECK_THROWS(five_kg + one_km);
    CHECK_THROWS(one_km - five_kg);
    CHECK_THROWS(five_kg - one_km);
}

TEST_CASE("Unary + and - operator"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits one_km{1, "km"};
    NumberWithUnits three_meters{3, "m"};

    CHECK_EQ(-one_km, NumberWithUnits{-1, "km"});
    CHECK_EQ(-three_meters, NumberWithUnits{-3, "m"});
    CHECK_EQ(+one_km, NumberWithUnits{1, "km"});
    CHECK_EQ(+three_meters, NumberWithUnits{3, "m"});
}

TEST_CASE("Increase/decrease operators"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits seconds{5, "sec"};
    // ++ operator
    CHECK_EQ(seconds++, NumberWithUnits{5, "sec"});
    CHECK_EQ(seconds, NumberWithUnits{6, "sec"});
    
    CHECK_EQ(++seconds, NumberWithUnits{7, "sec"});
    CHECK_EQ(seconds, NumberWithUnits{7, "sec"});

    NumberWithUnits grams{50, "g"};
    //-- operator
    CHECK_EQ(grams--, NumberWithUnits{50, "g"});
    CHECK_EQ(grams, NumberWithUnits{49, "g"});

    CHECK_EQ(--grams, NumberWithUnits{48, "g"});
    CHECK_EQ(grams, NumberWithUnits{48, "g"});
}

TEST_CASE("+=, -= operators"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits tons{2, "ton"};
    NumberWithUnits kilograms{200, "kg"};
    // += operator
    CHECK((tons+=kilograms) == NumberWithUnits{2.2, "ton"});
    CHECK(tons == NumberWithUnits{2.2, "ton"});
    CHECK(kilograms == NumberWithUnits{200, "kg"});

    NumberWithUnits kilometers{2, "km"};
    NumberWithUnits meters{200, "m"};
    // -= operator
    CHECK((kilometers-=meters) == NumberWithUnits{1.8, "km"});
    CHECK(kilometers == NumberWithUnits{1.8, "km"});
    CHECK(meters == NumberWithUnits{200, "m"});}

TEST_CASE("Multiplication operators"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits meters{10, "m"};

    //NumberWithUnits * double
    CHECK((meters*0.5) == NumberWithUnits{5, "m"});

    //double * NumberWithUnits
    CHECK((1.2*meters) == NumberWithUnits{12, "m"});

    //NumberWithUnits *= double
    CHECK((meters*=11.35) == NumberWithUnits{113.5, "m"});
    CHECK(meters == NumberWithUnits{113.5, "m"});
}

TEST_CASE("Comparison operators: {>, >=, <, <=, ==, !=}"){
    NumberWithUnits::read_units(units_file);

    // == operator
    CHECK_EQ(NumberWithUnits{100, "cm"}, NumberWithUnits{1, "m"});
    CHECK_EQ(NumberWithUnits{1, "m"}, NumberWithUnits{100, "cm"});
    CHECK_EQ(NumberWithUnits{1000, "g"}, NumberWithUnits{1, "kg"});
    CHECK_EQ(NumberWithUnits{1, "kg"}, NumberWithUnits{1000, "g"});

    // != operator
    CHECK_NE(NumberWithUnits{5, "min"}, NumberWithUnits{500, "sec"});
    CHECK_NE(NumberWithUnits{500, "sec"}, NumberWithUnits{5, "min"});
    CHECK_NE(NumberWithUnits{3, "ILS"}, NumberWithUnits{3, "USD"});
    CHECK_NE(NumberWithUnits{3, "USD"}, NumberWithUnits{3, "ILS"});

    // < and <= operator
    CHECK_LT(NumberWithUnits{2, "km"}, NumberWithUnits{3000, "m"});
    CHECK_LE(NumberWithUnits{2, "km"}, NumberWithUnits{3000, "m"});
    CHECK_LE(NumberWithUnits{2, "km"}, NumberWithUnits{2000, "m"});

    // > and >=operator
    CHECK_GT(NumberWithUnits{3000, "m"}, NumberWithUnits{2, "km"});
    CHECK_GE(NumberWithUnits{3000, "m"}, NumberWithUnits{2, "km"});
    CHECK_GE(NumberWithUnits{2000, "m"}, NumberWithUnits{2, "km"});

}