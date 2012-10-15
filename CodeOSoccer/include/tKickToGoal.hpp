#ifndef TKICKTOGOAL_HPP
#define TKICKTOGOAL_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TKickToGoal. 
  class TKickToGoal : public Tactic
  {
	public:
  
	/**Constructor taking state and botID as parameters.
	*@param state a belief state type variable
	*@param botID an integer which identifies the bot executing the tactic
	*@see BeliefState*/
    TKickToGoal(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { }
	
	/**Destructor.*/
    ~TKickToGoal()
    { } 
	
	/// An enumeration of internal states.
	enum InternalState
        {
                APPROACHING,
                SPINNING_CCW=-1,
                SPINNING_CW=1,      
                ATTACKING
        }iState;
        
	/**Checks if the tactic is of type active.*/
    inline bool isActiveTactic(void) const
    {
      return true;
    }

	/**@return the botID of the best bot for the given tactic among the free bots.
		 * @param freeBots list of botIDs of free bots
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param *tParam) const
    {
		int minv = *(freeBots.begin());
		int mindis = 10000;
		for (std::list<int>::const_iterator it = freeBots.begin(); it != freeBots.end(); ++it)
		{
			float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
			if(dis_from_ball < mindis)
			{
					dis_from_ball = mindis;
					minv = *it;
			}
		}
		return minv; /**The best bot for the tactic is the one closest to the ball. */
    }
	
	/**Executes tactic with given Tactic parameters.
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
    void execute(const Param& tParam)
    {           
		Vector2D<int> goal(HALF_FIELD_MAXX, 0); 
		float finalSlope = Vector2D<int>::angle(goal, state->homePos[botID]);
		float turnAngleLeft = normalizeAngle(finalSlope - state->homeAngle[botID]); // Angle left to turn
		float dist = Vector2D<int>::dist(state->ballPos, state->homePos[botID]);
		
		/**Goes to the ball if its distance from the bot is big.*/
		if(dist > BOT_BALL_THRESH)
		{
				sID = SkillSet::GoToBall;
				//printf("Going to ball %d, %f\n", BOT_BALL_THRESH, dist);
				skillSet->executeSkill(sID, sParam);
				return;
		}
		
		/**Turns to the goal if not within a threshold from it.*/
		if(fabs(turnAngleLeft) > 2 * SATISFIABLE_THETA)
		{
				sID = SkillSet::TurnToPoint;                    
				sParam.TurnToPointP.x = goal.x;
				sParam.TurnToPointP.y = goal.y;
				skillSet->executeSkill(sID, sParam);
				return;
		}
		
		/**Executes the kick.*/
		sID = SkillSet::Kick;
		sParam.KickP.power = 7;
		skillSet->executeSkill(sID, sParam);
		
		/**Tactic completed.*/
		if (state->homePos[botID].absSq() < BOT_BALL_THRESH * BOT_BALL_THRESH)
		{
				tState = COMPLETED;
		}
    }
  }; // class TKickToGoal
} // namespace Strategy

#endif // TKICKTOGOAL_HPP