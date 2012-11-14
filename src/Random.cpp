#include "Main.hpp"

//------------------------------- Instance ------------------------------------
//
// This class is a singleton
//
//-----------------------------------------------------------------------------
TCODRandom *Random::Instance()
{
	// Initialze random number generator with global seed value
	static TCODRandom instance; // = TCODRandom(seed, TCOD_RNG_CMWC);
	return &instance;
}
