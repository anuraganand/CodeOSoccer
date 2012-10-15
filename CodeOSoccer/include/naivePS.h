#pragma once

#ifndef NAIVE_PS_H
#define NAIVE_PS_H

#include "play.hpp"
#include "ps.h"

namespace Strategy
{
  /**Forward Declaratons.*/
  class BeliefState;

  /**@class NaivePS Class for beginners level play seection. */
  class NaivePS : public PS
  {
  public:
   /**Parameterised constructor for class.
    *@param state BeliefState variable for current state of game
    *@see BeliefState*/
    NaivePS(const BeliefState& state);

     /**Destructor for NaivePS.*/
    ~NaivePS();

    
    /**void type function to update the weights of each play.
    *@param termResult variable of type Play->Result */
    void updateWeights(Play::Result termResult) const;
  }; // class NaivePS
} // namespace Strategy

#endif // NAIVE_PS_H
