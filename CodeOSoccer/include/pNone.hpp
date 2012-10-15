#ifndef PNONE_HPP
#define PNONE_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

namespace Strategy
{
  /**@class defining PNone , a play of no type.*/
  class PNone : public Play
  {
  public:
  /**Constructor.
  *@param state BeliefState type variable holding game state
  *@see BeliefState*/
    inline PNone(const BeliefState& state) 
      : Play(state)
    {
      name = "None";
    }

    /**Destructor.*/
    inline ~PNone()
    { }

    /**Function to test applicability conditions for this play.
    *return False since its never applicable*/
    inline bool applicable(void) const
    {
      return false; // Should always be false as this the None play
    }

    /**Function to check wether the paly has been completed.
    *return Completed since none play is always completed*/
    inline Result done(void) const
    {
      return COMPLETED;
    }
  }; // class PNone
} // namespace Strategy

#endif // PNONE_HPP
