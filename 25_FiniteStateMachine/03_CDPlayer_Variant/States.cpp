/**
 * ============================================================================
 * File: States.cpp
 * 
 * --- DESIGN OVERVIEW:
 * This file contains the implementation of all state behaviors.
 * 
 * --- RAII (Resource Acquisition Is Initialization):
 * Instead of explicit onEntry/onExit calls, we use constructors to turn 
 * lights ON and destructors to turn them OFF. This guarantees that the 
 * hardware state (lights) is always synchronized with the software state.
 * ============================================================================
 */

#include "FSM.h"

//--------------------------------------------------------- Closed_without_CD:
Closed_without_CD::Closed_without_CD(FSM* f) : fsm(f) { }
Closed_without_CD::~Closed_without_CD() { }
void Closed_without_CD::open()          { fsm->transitionTo<Open_without_CD>(&FSM::open_tray); }
void Closed_without_CD::close()         { }
void Closed_without_CD::insert_CD(int)  { throw ">>> The CD player has been destroyed inserting a CD by force!\n"; }
void Closed_without_CD::remove_CD()     { throw ">>> The CD player has been destroyed removing a CD by force!\n"; }
void Closed_without_CD::play()          { }
void Closed_without_CD::stop()          { }
void Closed_without_CD::next_song()     { }
void Closed_without_CD::previous_song() { }
void Closed_without_CD::pause()         { }

//--------------------------------------------------------- Open_without_CD:
Open_without_CD::Open_without_CD(FSM* f) : fsm(f) { }
Open_without_CD::~Open_without_CD()   { }
void Open_without_CD::open()          { }
void Open_without_CD::close()         { fsm->transitionTo<Closed_without_CD>(&FSM::close_tray); }
void Open_without_CD::insert_CD(int n)
{
   fsm->nSongs = n;
   std::cout << fsm->name << ": A CD has been inserted.\n";
   fsm->CD_on_tray = true;
   fsm->transitionTo<Open_with_CD>();
}
void Open_without_CD::remove_CD()     { throw ">>> The CD player has been destroyed removing a CD by force!\n"; }
void Open_without_CD::play()          { }
void Open_without_CD::stop()          { }
void Open_without_CD::next_song()     { }
void Open_without_CD::previous_song() { }
void Open_without_CD::pause() { }

//--------------------------------------------------------- Open_with_CD:
Open_with_CD::Open_with_CD(FSM* f) : fsm(f) { }
Open_with_CD::~Open_with_CD()      { }
void Open_with_CD::open()          { }
void Open_with_CD::close()         { fsm->transitionTo<Closed_with_CD>(&FSM::close_tray_and_dir); }
void Open_with_CD::insert_CD(int)  { throw ">>> The CD player has been destroyed inserting a CD by force!\n"; }
void Open_with_CD::remove_CD()
{
   fsm->nSongs = 0;
   std::cout << fsm->name << ": A CD has been removed.\n";
   fsm->CD_on_tray = false;
   fsm->transitionTo<Open_without_CD>();
}
void Open_with_CD::play()          { fsm->transitionTo<Playing>(&FSM::close_tray_and_dir); }
void Open_with_CD::stop()          { }
void Open_with_CD::next_song()     { }
void Open_with_CD::previous_song() { }
void Open_with_CD::pause()         { }

//--------------------------------------------------------- Closed_with_CD:
Closed_with_CD::Closed_with_CD(FSM* f) : fsm(f)
{
   std::cout << fsm->name << ": Turning ON yellow light.\n";
   fsm->yellow_light_on = true;
}
Closed_with_CD::~Closed_with_CD()
{
   std::cout << fsm->name << ": Turning OFF yellow light.\n";
   fsm->yellow_light_on = false;
}
void Closed_with_CD::open()          { fsm->transitionTo<Open_with_CD>(&FSM::open_tray); }
void Closed_with_CD::close()         { }
void Closed_with_CD::insert_CD(int)  { throw ">>> The CD player has been destroyed inserting a CD by force!\n"; }
void Closed_with_CD::remove_CD()     { throw ">>> The CD player has been destroyed removing a CD by force!\n"; }
void Closed_with_CD::play()          { fsm->transitionTo<Playing>(&FSM::reset); }
void Closed_with_CD::stop()          { }
void Closed_with_CD::next_song()     { }
void Closed_with_CD::previous_song() { }
void Closed_with_CD::pause()         { }

//--------------------------------------------------------- Playing:
Playing::Playing(FSM* f) : fsm(f)
{
   std::cout << fsm->name << ": Turning ON green light.\n";
   fsm->green_light_on = true;
   std::cout << fsm->name << ": Playing song number " << fsm->iSong << '\n';
   fsm->playing = true;
}
Playing::~Playing()
{
   std::cout << fsm->name << ": Stop playing.\n";
   fsm->playing = false;
   std::cout << fsm->name << ": Turning OFF green light.\n";
   fsm->green_light_on = false;
}
void Playing::open()         { fsm->transitionTo<Open_with_CD>(&FSM::open_tray); }
void Playing::close()        { }
void Playing::insert_CD(int) { throw ">>> The CD player has been destroyed inserting a CD by force!\n"; }
void Playing::remove_CD()    { throw ">>> The CD player has been destroyed removing a CD by force!\n"; }
void Playing::play()         { fsm->transitionTo<Playing>(&FSM::reset); }
void Playing::stop()         { fsm->transitionTo<Closed_with_CD>(); }
void Playing::next_song()
{
   fsm->iSong = fsm->iSong < fsm->nSongs ? fsm->iSong + 1 : 1;
   std::cout << fsm->name << ": Playing song number " << fsm->iSong << '\n';
}
void Playing::previous_song()
{
   fsm->iSong = fsm->iSong > 1 ? fsm->iSong - 1 : fsm->nSongs;
   std::cout << fsm->name << ": Playing song number " << fsm->iSong << '\n';
}
void Playing::pause() { fsm->transitionTo<Paused>(); }

//--------------------------------------------------------- Paused:
Paused::Paused(FSM* f) : fsm(f)
{
   std::cout << fsm->name << ": Turning ON cian light.\n";
   fsm->cian_light_on = true;
}
Paused::~Paused()
{
   std::cout << fsm->name << ": Turning OFF cian light.\n";
   fsm->cian_light_on = false;
}
void Paused::open() { fsm->transitionTo<Open_with_CD>(&FSM::open_tray); }
void Paused::close() { }
void Paused::insert_CD(int)  { throw ">>> The CD player has been destroyed inserting a CD by force!\n"; }
void Paused::remove_CD()     { throw ">>> The CD player has been destroyed removing a CD by force!\n"; }
void Paused::play()          { fsm->transitionTo<Playing>(); }
void Paused::stop()          { fsm->transitionTo<Closed_with_CD>(); }
void Paused::next_song()     { }
void Paused::previous_song() { }
void Paused::pause()         { }

//================================================================================ END
