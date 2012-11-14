#include "Main.hpp"

// Uncomment below to display message info
//#define SHOW_MESSAGING_INFO

//------------------------------- Instance ------------------------------------
//
// This class is a singleton
//
//-----------------------------------------------------------------------------
MessageTransmitter *MessageTransmitter::Instance()
{
	static MessageTransmitter instance; 
	return &instance;
}

//--------------------------------- Send --------------------------------------
//
// This method routes a message to a receiver entity
//
//-----------------------------------------------------------------------------
void MessageTransmitter::Send(Entity *pReceiver, int msg)
{
	// Make sure the receiver is valid
	if(pReceiver == NULL)
	{
		cout << "Warning! No Valid Receiver found" << endl;
		return;
	}

	// Create the Message
	Message Msg = Message(pReceiver->ID(), msg);

#ifdef SHOW_MESSAGING_INFO
	// Transmit the message
	cout << "Message Transmited to Entity # " << pReceiver->ID() << ", Msg: " << msg << endl;
#endif

	// Send the Message to the recipient
	if(!pReceiver->HandleMessage(Msg))
	{
		// Message could not be handled
		cout << "Message could not be handled" << endl;
	}
}

//--------------------------------- Send --------------------------------------
//
// This method routes a message with data to a receiver module
//
//-----------------------------------------------------------------------------
void MessageTransmitter::Send(Module *pReceiver, int msg, string data)
{
	// Make sure the receiver is valid
	if(pReceiver == NULL)
	{
		cout << "Warning! No Valid Sender Module Found" << endl;
		return;
	}

	// Create the Message
	Message Msg = Message(-1, msg, data);

#ifdef SHOW_MESSAGING_INFO
	// Transmit the message
	cout << "Message Transmited to Module, Msg: " << data << endl;
#endif

	// Send the Message to the recipient
	if(!pReceiver->HandleMessage(Msg))
	{
		// Message could not be handled
		cout << "Message could not be handled" << endl;
	}
}

//--------------------------------- Send --------------------------------------
//
// This method routes a message to a receiver GameEngineClass
//
//-----------------------------------------------------------------------------
void MessageTransmitter::Send(GameEngineClass *pReceiver, int msg)
{
	// Make sure the receiver is valid
	if(pReceiver == NULL)
	{
		cout << "Warning! No Valid Receiver GameEngine found" << endl;
		return;
	}

	// Create the Message
	Message Msg = Message(-1, msg);

#ifdef SHOW_MESSAGING_INFO
	// Transmit the message
	cout << "Message Transmited to GameEngine, Msg: " << msg << endl;
#endif

	// Send the Message to the recipient
	if(!pReceiver->Receive(Msg))
	{
		// Message could not be handled
		cout << "Message could not be handled" << endl;
	}
}
