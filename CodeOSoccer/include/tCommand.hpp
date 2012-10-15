#ifndef TCommand_HPP
#define TCommand_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"

namespace Strategy
{
	/**Class for Tactic TCommand.*/ 
  class TCommand : public Tactic
  {
	public:
	
	/**Constructor taking state and botID as parameters.
	*@param state a belief state type variable
	*@param botID an integer which identifies the bot executing the tactic
	*@see BeliefState*/
    TCommand(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { } 
	
	/**Destructor.*/
    ~TCommand()
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
       return -1;
    } 

	/**Executes tactic with given Tactic parameters.
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
    void execute(const Param& tParam)
    {
      sID = SkillSet::Dummy;
      sParam.DummyP.v_y=tParam.CommandP.v_y;
	  sParam.DummyP.v_x=tParam.CommandP.v_x;
	  sParam.DummyP.v_t=tParam.CommandP.v_t;
	  sParam.DummyP.power=tParam.CommandP.power;
	  sParam.DummyP.dribble=tParam.CommandP.dribble;
      skillSet->executeSkill(sID, sParam);
    }
  }; // class TCommand
} // namespace Strategy

#endif // TCommand_HPP