#ifndef MESSAGE_HPP
#define MESSAGE_HPP
//------------------------------------------------------------------------
//
// Name: Message.hpp
//
// Desc: This defines a Message. A Message is a data structure that
//			 records information required to dispatch messages. Messages 
//			 are used by game agents to communicate with each other.
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

struct Message
{
	// The entity that is to receive this Message
	int Receiver;

	// The message itself. These are all enumerated in the file "MessageTypes.h"
	int Msg;

	// Extra data passed along with the message (e.g. Content)
	string data;

	Message() : Receiver(ENTITY_DEFAULT), Msg(MSG_DEFAULT){data = "";}

	Message(int receiver, int msg) : Receiver(receiver), Msg(msg){data = "";}

	Message(int receiver, int msg, string str) : Receiver(receiver), Msg(msg){data = str;}

};

#endif
