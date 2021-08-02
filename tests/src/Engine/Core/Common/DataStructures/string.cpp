#include <catch2/catch.hpp>
#include <Core/Common/DataStructures/string.hpp>

TEST_CASE("Long String Set Capacity & GetCapacity", "[Long String]")
{
	using namespace liq;
	
	long_string str;
	
	// ----------- With incorrect capacity encoding -----------------
	
	str.capacity = 1;
	REQUIRE(str.GetCapacity()==2);
	REQUIRE(str.capacity == 0b00000001);
	
	str.capacity = 2;
	REQUIRE(str.GetCapacity()==4);
	REQUIRE(str.capacity == 0b00000010);
	
	str.capacity = 3;
	REQUIRE(str.GetCapacity()==6);
	REQUIRE(str.capacity == 0b00000011);
	
	// ----------- With correct capacity encoding ----------------
	
	str.SetCapacity(2);
	REQUIRE(str.GetCapacity() == 2);
    REQUIRE(str.capacity == 0b1000000000000000000000000000000000000000000000000000000000000001);
	
	str.SetCapacity(1);
	REQUIRE(str.GetCapacity()==2);
    REQUIRE(str.capacity == 0b1000000000000000000000000000000000000000000000000000000000000001);
	
	str.SetCapacity(3);
	REQUIRE(str.GetCapacity()==4);
    REQUIRE(str.capacity == 0b1000000000000000000000000000000000000000000000000000000000000010);
	
	str.SetCapacity(4);
	REQUIRE(str.GetCapacity()==4);
    REQUIRE(str.capacity == 0b1000000000000000000000000000000000000000000000000000000000000010);
	
	// ------------ Edge cases with correct encoding -------------
	
	//NOTE(Tiago): the reason the results differ is the encoding scheme.
}

TEST_CASE("Long String Comparison Operator Tests (operator==)", "[Long String]")
{
	using namespace liq;
	
	long_string str1("string1");
	long_string str2("string2");
	long_string str3("string1");
	
	REQUIRE((str1 == str2) == false);
	REQUIRE((str1 == str3) == true);
	REQUIRE((str3 == str2) == false);
}
	
	