#ifndef MODULE_HPP
#define MODULE_HPP
//------------------------------------------------------------------------
//
// Name: Module.hpp
//
// Desc: Base class to define a common interface for all modules
//
// Author: Chris Capobianco, 2012-10-06
//
//------------------------------------------------------------------------
#include "Global.hpp"

class Module
{
public:

	Module(){}
	~Module(){}

	virtual bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;};
	virtual void Render() = 0;
	virtual bool HandleMessage(const Message &msg){return true;}

};
 
#endif
