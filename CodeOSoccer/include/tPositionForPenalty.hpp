#ifndef TPOSITIONFORPENALTY_HPP
#define TPOSITIONFORPENALTY_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TPositionForPenalty.
  class TPositionForPenalty : public Tactic
  {   
    public:

	/**Constructor taking state and botID as parameters.
	*@param state a belief state type variable
	*@param botID an integer which identifies the bot executing the tactic
	*@see BeliefState*/
    TPositionForPenalty(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { }
	
	/**Destructor.*/
    ~TPositionForPenalty()
    { } 
	
	/**Checks if the tactic is of type active.*/
	inline bool isActiveTactic(void) const
    {
      return false;
    }
	
	/**@return the botID of the best bot for the given tactic among the free bots.
	 * @param freeBots list of botIDs of free bots
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
	int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
			int minv = *(freeBots.begin());
			int mindis = 10;
			for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				float dis_from_point = (state->homePos[*it] - state->ballPos).absSq();
				if(dis_from_point < mindis)
				{
					dis_from_point = mindis;
					minv = *it;
				}
			}
			return minv;	/**The best bot for the tactic is the one closest to the ball. */
    }

	/**Executes tactic with given Tactic parameters.
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
    void execute(const Param& tParam)
    {
		/**Calls GoToPoint with given target point*/
       sID = SkillSet::GoToPoint;
       sParam.GoToPointP.x          = tParam.PositionForPenaltyP.x ;
       sParam.GoToPointP.y          = tParam.PositionForPenaltyP.y;
       sParam.GoToPointP.finalslope = tParam.PositionForPenaltyP.finalSlope ;
       sParam.GoToPointP.finalVelocity= tParam.PositionForPenaltyP.finalVelocity ;     
	   skillSet->executeSkill(sID, sParam);
      
	  /**Tactic completed if target point reached.*/
      if((state->homePos[botID] - Vector2D<int>(tParam.PositionForPenaltyP.x, tParam.PositionForPenaltyP.y)).absSq() < BOT_POINT_THRESH * BOT_POINT_THRESH) 
		{
			tState = COMPLETED;
		}
    }
  }; // class TPositionForPenalty
} // namespace Strategy

#endif // TPOSITIONFORPENALTY_HPP
  