#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for SoundIdle
//
//------------------------------------------------------------------------
SoundIdle *SoundIdle::Instance()
{
	static SoundIdle instance;
	return &instance;
}
bool SoundIdle::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundIdle::Render(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundMainMenu
//
//------------------------------------------------------------------------
SoundMainMenu *SoundMainMenu::Instance()
{
	static SoundMainMenu instance;
	return &instance;
}

void SoundMainMenu::Enter(SoundClass *sound){}
bool SoundMainMenu::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundMainMenu::Render(SoundClass *sound){}
void SoundMainMenu::Exit(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundNew
//
//------------------------------------------------------------------------
SoundNew *SoundNew::Instance()
{
	static SoundNew instance;
	return &instance;
}

void SoundNew::Enter(SoundClass *sound){}
bool SoundNew::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundNew::Render(SoundClass *sound){}
void SoundNew::Exit(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundWorld
//
//------------------------------------------------------------------------
SoundWorld *SoundWorld::Instance()
{
	static SoundWorld instance;
	return &instance;
}

void SoundWorld::Enter(SoundClass *sound){}
bool SoundWorld::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundWorld::Render(SoundClass *sound){}
void SoundWorld::Exit(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundTemple
//
//------------------------------------------------------------------------
SoundTemple *SoundTemple::Instance()
{
	static SoundTemple instance;
	return &instance;
}

void SoundTemple::Enter(SoundClass *sound){}
bool SoundTemple::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundTemple::Render(SoundClass *sound){}
void SoundTemple::Exit(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundTown
//
//------------------------------------------------------------------------
SoundTown *SoundTown::Instance()
{
	static SoundTown instance;
	return &instance;
}

void SoundTown::Enter(SoundClass *sound){}
bool SoundTown::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundTown::Render(SoundClass *sound){}
void SoundTown::Exit(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundCave
//
//------------------------------------------------------------------------
SoundCave *SoundCave::Instance()
{
	static SoundCave instance;
	return &instance;
}

void SoundCave::Enter(SoundClass *sound){}
bool SoundCave::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundCave::Render(SoundClass *sound){}
void SoundCave::Exit(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundRest
//
//------------------------------------------------------------------------
SoundRest *SoundRest::Instance()
{
	static SoundRest instance;
	return &instance;
}

void SoundRest::Enter(SoundClass *sound){}
bool SoundRest::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundRest::Render(SoundClass *sound)
{
	// Pause for Rest Music
	usleep(1750000);
}
void SoundRest::Exit(SoundClass *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundQuit
//
//------------------------------------------------------------------------
SoundQuit *SoundQuit::Instance()
{
	static SoundQuit instance;
	return &instance;
}

void SoundQuit::Enter(SoundClass *sound){}
bool SoundQuit::Update(SoundClass *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return false;}
void SoundQuit::Render(SoundClass *sound){}
void SoundQuit::Exit(SoundClass *sound){}
