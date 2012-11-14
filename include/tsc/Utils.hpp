#ifndef UTILS_HPP
#define UTILS_HPP
//------------------------------------------------------------------------
//
//  Name: Utils.hpp
//
//  Desc: Misc utility functions and constants
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "Global.hpp"

//a few useful constants
const int MaxInt = (std::numeric_limits<int>::max)();
const double MaxDouble = (std::numeric_limits<double>::max)();
const double MinDouble = (std::numeric_limits<double>::min)();
const float MaxFloat = (std::numeric_limits<float>::max)();
const float MinFloat = (std::numeric_limits<float>::min)();

const double Pi = 3.14159265358979324f;
const double TwoPi = 2.0f*Pi;

// Returns true is the third parameter is in the range described by the first two
template <typename T>
inline bool InRange(T &start, T &end, T &val)
{
	if(start < end)
	{
		if( (val > start) && (val < end) ) return true;
		else return false;
	}
	else
	{
		if( (val < start) && (val > end) ) return true;
		else return false;
	}
}

// Returns the maximum of two values
template <class T>
inline T Max(const T &a, const T &b)
{
  if(a > b) return a; return b;
}

// Returns the minimum of two values
template <class T>
inline T Min(const T &a, const T &b)
{
  if(a < b) return a; return b;
}

// Clamps the first argument between the second two
template <class T>
inline void Clamp(T &arg, const T &minVal, const T &maxVal)
{
  assert ( (static_cast<double>(minVal) < static_cast<double>(maxVal)) && "Clamp:: MaxVal < MinVal!");

  if(arg < minVal)
  {
    arg = minVal;
  }

  if(arg > maxVal)
  {
    arg = maxVal;
  }
}

#endif
