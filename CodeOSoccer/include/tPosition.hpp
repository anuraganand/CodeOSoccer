#ifndef TPOSITION_HPP
#define TPOSITION_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"
#include <sys/time.h>
#include <unistd.h>
namespace Strategy
{
	///Class for Tactic TPosition.
  class TPosition: public Tactic
  {   
	public:  
    
	/**Constructor taking state and botID as parameters.
	*@param state a belief state type variable
	*@param botID an integer which identifies the bot executing the tactic
	*@see BeliefState*/
    TPosition(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { } 

	/**Destructor.*/
    ~TPosition()
    { } 
	
	/**Checks if the tactic is of type active.*/
    inline bool isActiveTactic(void) const
    {
      return false;
    }

	/**Returns the botID of the best bot for the given tactic among the free bots.
	 * @param freeBots list of botIDs of free bots
	 * @param tParam tactic parameters
	 * @see Tactic::Param
	 * @return The best bot for the tactic is the one closest to the target point.*/
    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
		assert(tParam != 0);
		int minv   = *(freeBots.begin());
		int mindis = 1000000000;
		Vector2D<int> tGoToPoint(tParam->PositionP.x, tParam->PositionP.y);
		for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
		{
			float dis_from_point = (state->homePos[*it] - tGoToPoint).absSq();
			if(*it == botID)
				dis_from_point -=HYSTERESIS;
			if(dis_from_point < mindis)
			{
				mindis = dis_from_point;
				minv = *it;
			}
		}
		printf("%d assigned Position\n", minv);
		return minv;		
    }
	
	/**Executes tactic with given Tactic parameters.
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
    void execute(const Param& tParam)
    {
		/**Calls GoToPoint with given target point*/
      sID = SkillSet::GoToPoint;
      sParam.GoToPointP.x          = tParam.PositionP.x ;
      sParam.GoToPointP.y          = tParam.PositionP.y ;
      sParam.GoToPointP.align      = tParam.PositionP.align;
      sParam.GoToPointP.finalslope = tParam.PositionP.finalSlope ;
      sParam.GoToPointP.finalVelocity = tParam.PositionP.finalVelocity;
	  skillSet->executeSkill(sID, sParam);
		
		/**Tactic completed if target point reached.*/
		if((state->homePos[botID] - Vector2D<int>(tParam.PositionP.x, tParam.PositionP.y)).absSq() < BOT_POINT_THRESH * BOT_POINT_THRESH) 
		{
			tState = COMPLETED;
		}
    }
  }; // class TPosition
} // namespace Strategy

#endif // TPOSITION_HPP
  