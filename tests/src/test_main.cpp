#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <Core/Common/DataStructures/string.hpp>

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
	liq::long_string str;
	str.capacity = 1;
	
	uint64 cap = str.GetCapacity();
	
	REQUIRE(cap == 2);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}