#include <catch2/catch.hpp>
#include <Core/Common/DataStructures/string.hpp>

TEST_CASE("Set Capacity & Get Capacity", "[Long String]")
{
	using namespace liq;
	
	long_string str;
	
	SECTION("With incorrect capacity encoding")
	{
		str.capacity = 1;
		REQUIRE(str.GetCapacity()==2);
		REQUIRE(str.capacity == 0b00000001);
		
		str.capacity = 2;
		REQUIRE(str.GetCapacity()==4);
		REQUIRE(str.capacity == 0b00000010);
		
		str.capacity = 3;
		REQUIRE(str.GetCapacity()==6);
		REQUIRE(str.capacity == 0b00000011);
	}
	
	SECTION("With correct capacity encoding")
	{
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
	}
}

TEST_CASE("Comparison Operator With Long String ( operator==(const long_string&) )", "[Long String]")
{
    using namespace liq;
	
    SECTION("Same size long strings strings")
    {
        long_string str1("string1");
        long_string str2("string2");
        long_string str3("string1");

        REQUIRE_FALSE(str1 == str2);
        REQUIRE(str1 == str3);
        REQUIRE_FALSE(str3 == str2);
    }

    SECTION("Different Size long Strings")
    {
        long_string str1("abcdefghjk");
        long_string str2("abc");

	REQUIRE_FALSE(str1 == str2);
    }
	
    SECTION("Different capacity magnitude strings")
    {
	long_string str1("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	long_string str2("b");
		
	REQUIRE_FALSE(str1 == str2);
	REQUIRE_FALSE(str2 == str1);
	REQUIRE(str1 == str1);
	REQUIRE(str2 == str2);
    }
}

TEST_CASE("Comparison operator with string literals ( operator==(const char (&other)[length] )", "[Long String]")
{
    using namespace liq;

    SECTION("Same size string literals")
    {
        long_string str("string1");

		REQUIRE_FALSE(str == "string2");
        REQUIRE(str == "string1");
        REQUIRE_FALSE("string2" == str);
    }

    SECTION("Diffrent size string literals")
    {
        long_string str("string1");

		REQUIRE_FALSE(str == "abcdefgh");
        REQUIRE_FALSE("abcdefghsadflkufdsakjdfasbn"  == str);
    }

}

TEST_CASE("concatenation operator with long_string ( operator+(const long_string&) )", "[Long String]")
{
  SECTION("Isolated String")
  {
    liq::long_string str1 = "st1";
    liq::long_string str2 = "st2";
    liq::long_string str3 = str1 + str2;

    REQUIRE(str3 == "st1st2");
  }
}

TEST_CASE("append operator with long string ( operator+=(const long_string&) )", "[Long String]")
{
  using namespace liq;
  long_string str1 = "st1";
  long_string str2 = "st2";
  str1 += str2;

  REQUIRE(str1 == "st1st2");
}
