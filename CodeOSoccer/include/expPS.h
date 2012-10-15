#ifndef EXP_PS_H
#define EXP_PS_H

#include "ps.h"
#include "play.hpp"

namespace Strategy
{
  /**Forward declaration.*/
  class BeliefState;

  /**@class ExpPS Class for expert level play seection. */
  class ExpPS : public PS
  {
  public:
    /**Parameterised constructor for class.
    *@param state BeliefState variable for current state of game
    *@see BeliefState*/
    ExpPS(const BeliefState& state);

    /**Destructor for ExpPS.*/
    ~ExpPS();

    /**void type function to update the weights of each play.
    *@param termResult variable of type Play->Result */
    void updateWeights(Play::Result termResult) const;

  }; // class ExpPS
} // namespace Strategy

#endif // EXP_PS_H
