#ifndef TSTOP_HPP
#define TSTOP_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TStop.
  class TStop : public Tactic
  {
	public:
  
	/**Constructor taking state and botID as parameters.
	*@param state a belief state type variable
	*@param botID an integer which identifies the bot executing the tactic
	*@see BeliefState*/
    TStop(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { }
	
	///Destructor.
    ~TStop()
    { }
	
	/**Checks if the tactic is of type active.*/
    inline bool isActiveTactic(void) const
    {
      return false;
    }

	/**Returns the botID of the best bot for the given tactic among the free bots.
	 * @param freeBots list of botIDs of free bots
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
      for (std::list<int>::iterator it=freeBots.begin(); it!=freeBots.end(); ++it)
      {
        return *it;
      }
      Util::Logger::abort("No bot available for role assignment");
      return -1;
    }
	
	/**Executes tactic with given Tactic parameters.
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
    void execute(const Param& tParam)
    {
      
      sID = SkillSet::Stop;
      skillSet->executeSkill(sID, sParam);

		/**Tactic completed if bot stopped.*/
      if (state->homeVel[botID].absSq() < ZERO_VELOCITY_THRESHOLD*ZERO_VELOCITY_THRESHOLD)
      {
        tState = COMPLETED;
      }
    }
  }; // class TStop
} // namespace Strategy

#endif // TSTOP_HPP
