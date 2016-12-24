// Spaceshipify.cpp : Defines the entry point for the console application.
//

// The C standard library used by VS2015 gives us a strcmp that seems to always return values from {-1,0,1}
// so it's all for nothing.

#include "stdafx.h"

#include "string.h"


#include <limits.h>

/**
 *  Make things harder by returning 'extreme' values, far from the 'nice' {-1,0,1} set
 */
int strcmp_scrambled(const char * const arg1, const char * const arg2) {
	const int s = strcmp(arg1, arg2);

	int ret = 0; // assume the zero case, to start with

	// SHRT_* not INT_* because we play with <short> later; don't want extreme int vals
	if      (s < 0) { ret = SHRT_MIN; }  // handle negative case
	else if (s > 0) { ret = SHRT_MAX; }; // handle positive case

	return ret;
}

#define strcmp strcmp_scrambled ///////////////////!!!!!!!!!!!!!!!!!!!!!

int spaceshipify_int(const int arg) {
	int ret = (arg > 0) - (arg < 0);
	return ret;
}

/**/
template<class T> T spaceshipify(T arg) {
	T ret = static_cast<T>( (arg > 0) - (arg < 0) );
	return ret;
};
/**/
//#include <algorithm>
//#undef min


// TODO template version, using something like is_signed_integer_type 

const char * const str1 = "1000";
const char * const str2 = "1001";
const char * const str3 = "1002";
const char * const str4 = "2345";

void evaluateSpaceship(const int arg) {

	//std::min(3, 4);

	switch (arg) {
	case -1:
		puts("-1: Second string greater");
		break;
	case 0:
		puts("0: strings equal");
		break;
	case 1:
		puts("1: First string greater");
		break;

	default:
		fputs("Invalid input value\n",stderr);
		break;
	}
}


// #define spaceshipify_int spaceshipify

#include <type_traits>

int main()
{
	int cmp = strcmp(str1,str1);
	int spaceship = spaceshipify(cmp);
	evaluateSpaceship(spaceship);


	cmp = strcmp(str1, str2);
	spaceship = spaceshipify(cmp);
	evaluateSpaceship(spaceship);

	
	//(typeof str2) mmm;

	cmp = strcmp(str2, str4);
	short cmp_short = (short)cmp;
	auto spaceship_short = spaceshipify(cmp_short);
	static_assert( std::is_same<decltype(spaceship_short),short>::value, "Unexpected 'auto' type: should be short" );
	
	evaluateSpaceship(spaceship_short);


	cmp = strcmp(str2, str1);
	spaceship = spaceshipify(cmp);
	evaluateSpaceship(spaceship);
	
	cmp = strcmp(str4, str1);
	spaceship = spaceshipify(cmp);
	evaluateSpaceship(spaceship);

	puts("Press enter to exit");
	getc(stdin);
    return 0;
}

