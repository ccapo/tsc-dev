#ifndef RANDOM_HPP
#define RANDOM_HPP
//------------------------------------------------------------------------
//
// Name: Random.hpp
//
// Desc: Singleton class to handle the random number generator
//
// Author: Chris Capobianco, 2012-10-06
//
//------------------------------------------------------------------------
#include "Global.hpp"

// Provide easy access
#define RNG Random::Instance()

class Random
{
private:

	Random(){}

	// Copy ctor and assignment should be private
	Random(const Random&);
	Random &operator=(const Random&);

public:

	// This is a singleton
	static TCODRandom *Instance();

};

#endif
