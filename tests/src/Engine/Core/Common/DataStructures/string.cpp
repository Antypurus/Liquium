#include <catch2/catch.hpp>
#include <Core/Common/DataStructures/string.hpp>

TEST_CASE("Long String Set Capacity & GetCapacity", "[Long String]")
{
	using namespace liq;
	
	long_string str;
	
	str.capacity = 1;
	REQUIRE(str.GetCapacity()==2);
	str.capacity = 2;
	REQUIRE(str.GetCapacity()==4);
	str.capacity = 3;
	REQUIRE(str.GetCapacity()==6);
	
	str.SetCapacity(2);
	REQUIRE(str.GetCapacity()==2);
	str.SetCapacity(1);
	REQUIRE(str.GetCapacity()==2);
	str.SetCapacity(3);
	REQUIRE(str.GetCapacity()==4);
	str.SetCapacity(4);
	REQUIRE(str.GetCapacity()==4);
}
	
	