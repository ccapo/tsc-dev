#ifndef MESSAGETRANSMITTER_HPP
#define MESSAGETRANSMITTER_HPP
//------------------------------------------------------------------------
//
// Name: MessageTransmitter.hpp
//
// Desc: A message Transmitter. Manages messages of the type Message.
//			 Instantiated as a singleton.
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "Module.hpp"
#include "Engine.hpp"

// To make life easier...
#define Transmit MessageTransmitter::Instance()

class MessageTransmitter
{
private:

	MessageTransmitter(){}

	// Copy ctor and assignment should be private
	MessageTransmitter(const MessageTransmitter&);
	MessageTransmitter &operator=(const MessageTransmitter&);

public:

	static MessageTransmitter *Instance();

	// Send message msg to entity pReceiver
	void Send(Entity *pReceiver, int msg);

	// Send message msg to Engine pReceiver
	void Send(EngineClass *pReceiver, int msg);

	// Send message msg w/ data to module pReceiver
	void Send(Module *pReceiver, int msg, string data);

};

#endif
