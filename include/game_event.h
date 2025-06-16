#ifndef game_event_h
#define game_event_h

#include "event_base.h" 

class GameEvent : public event_base<4, void, size_t> {
public:

  enum events : unsigned int {

    ROLL_EVENT,             
    SNAKE_LADDER_HIT_EVENT,
    WON_EVENT,            
    POS_EVENT            
  };

};

#endif
