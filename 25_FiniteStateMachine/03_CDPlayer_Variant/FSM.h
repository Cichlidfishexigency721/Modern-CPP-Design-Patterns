/**
 * ============================================================================
 * File: FSM.h (Modern State Machine with std::variant)
 * 
 * --- DESIGN OVERVIEW:
 * This implementation demonstrates a state machine using std::variant (C++17).
 * It is functionally identical to the GoF version (02_CDPlayer_GoF) but 
 * replaces the dynamic registry and virtual hierarchy with type-safe 
 * value semantics.
 * 
 * --- RAII & TRANSITIONS:
 * We use constructors/destructors to simulate onEntry/onExit behaviors.
 * The 'transitionTo' method ensures a clean transition by explicitly 
 * destroying the current state before instantiating the next one.
 * 
 * --- TYPE SAFETY:
 * The compiler ensures that only valid states defined in the 'StateVariant' 
 * can be used, eliminating the risk of malformed strings or null pointers.
 * ============================================================================
 */

#ifndef FSM_H
#define FSM_H

#include <iostream>
#include <string>
#include <variant>
#include <memory>
#include <stdexcept>

class FSM;

//--------------------------------------------------------- State Data Structs:
#define STATE_METHODS \
   void open(); void close(); void insert_CD(int n); void remove_CD(); \
   void play(); void stop(); void next_song(); void previous_song(); void pause();

struct Closed_without_CD { FSM* fsm; explicit Closed_without_CD(FSM* f); ~Closed_without_CD(); STATE_METHODS };
struct Open_without_CD   { FSM* fsm; explicit Open_without_CD(FSM* f);   ~Open_without_CD();   STATE_METHODS };
struct Open_with_CD      { FSM* fsm; explicit Open_with_CD(FSM* f);      ~Open_with_CD();      STATE_METHODS };
struct Closed_with_CD    { FSM* fsm; explicit Closed_with_CD(FSM* f);    ~Closed_with_CD();    STATE_METHODS };
struct Playing           { FSM* fsm; explicit Playing(FSM* f);           ~Playing();           STATE_METHODS };
struct Paused            { FSM* fsm; explicit Paused(FSM* f);            ~Paused();            STATE_METHODS };

// The variant including all states and std::monostate for transitions
using StateVariant = std::variant<
   std::monostate,    // Unit type intended for use as a well-behaved empty alternative in std::variant
                      // Set as its first alternative, makes the variant itself default-constructible
   Closed_without_CD, 
   Open_without_CD, 
   Open_with_CD, 
   Closed_with_CD, 
   Playing, 
   Paused
>;

//--------------------------------------------------------- FSM (Context):
class FSM
{
private:
   StateVariant state_;

public:
   std::string name     {""};
   bool tray_open       {false};
   bool playing         {false};
   bool green_light_on  {false};
   bool yellow_light_on {false};
   bool cian_light_on   {false};
   bool CD_on_tray      {false};
   int nSongs           {0};  // Number of songs in the CD
   int iSong            {0};  // Song that is being played

   FSM(std::string name, const std::string& initialStateName);

   // Transition helper
   template <typename T>
   void transitionTo(void(FSM::*action)() = nullptr)
   {
      // 1. Force destruction of current state (calls destructor / onExit)
      state_ = std::monostate{}; 

      // 2. Execute transition action
      if (action) (this->*action)();

      // 3. Construct new state (calls constructor / onEntry)
      state_.emplace<T>(this);
   }

   // Events (Public API)
   void open();
   void close();
   void insert_CD(int n);
   void remove_CD();
   void play();
   void stop();
   void next_song();
   void previous_song();
   void pause();

   // Transition actions
   void open_tray()  { std::cout << name << ": Opening tray.\n"; tray_open = true; }
   void close_tray() { std::cout << name << ": Closing tray.\n"; tray_open = false; }
   void close_tray_and_dir()
   {
      close_tray();
      std::cout << name << ": Reading CD directory with " << nSongs << " songs.\n";
      iSong = 1;
   }
   void reset() { std::cout << name << ": Resetting to play first song.\n"; iSong = 1; }
};

#endif
//================================================================================ END
