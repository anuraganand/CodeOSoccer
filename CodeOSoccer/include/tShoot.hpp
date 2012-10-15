#ifndef TSHOOT_HPP
#define TSHOOT_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
  ///Class for Tactic TShoot. 
  class TShoot : public Tactic
  {
	public:
  
	/**Constructor taking state and botID as parameters.
	*@param state a belief state type variable
	*@param botID an integer which identifies the bot executing the tactic
	*@see BeliefState*/
    TShoot(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { }
	
	///Destructor.
    ~TShoot()
    { } 
	
	/**Checks if the tactic is of type active.*/
    inline bool isActiveTactic(void) const
    {
      return true;
    }

	/**@return the botID of the best bot for the given tactic among the free bots.
	 * @param freeBots list of botIDs of free bots
	 * @param tParam tactic parameters
	 * @see Tactic::Param*/
    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
		int minv = *(freeBots.begin());
		int mindis = 10000;
		for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
		{
			float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
			if(dis_from_ball < mindis)
			{
				dis_from_ball = mindis;
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
      float tmp_angle1,tmp_angle2,tmp_angle3;
      float angle1,angle2,finalAngle;
      
      tmp_angle1 = Vector2D<int>::angle(Vector2D<int>(HALF_FIELD_MAXX,OPP_GOAL_MAXY),state->ballPos);
      tmp_angle2 = Vector2D<int>::angle(getOppGoalie(),state->ballPos);
      tmp_angle3 = Vector2D<int>::angle(Vector2D<int>(HALF_FIELD_MAXX,OPP_GOAL_MINY),state->ballPos);
      
      angle1 = fabs(tmp_angle2 - tmp_angle1);
      angle2 = fabs(tmp_angle3 - tmp_angle2);
	  /**Chooses the greater angle among opponent goalkeeper's position and goalpost extremes with respect current position of ball.
		* Makes finalangle to be half of the greater angle. */
      if(angle1 > angle2)
        finalAngle = (tmp_angle2 + tmp_angle1)/2;
      else
        finalAngle = (tmp_angle2 + tmp_angle3)/2;
      Util::Logger::toStdOut("Final Angle : %f\n",finalAngle);
      float dist_from_ball = Vector2D<int>::dist(state->homePos[botID],state->ballPos);
      if(dist_from_ball < BOT_BALL_THRESH)
      {
        sParam.GoToPointP.x = HALF_FIELD_MAXX;
        /* The point of intersection with the goal Vertical line y = mx1 + (y2 - mx2)*/
        sParam.GoToPointP.y = finalAngle*HALF_FIELD_MAXX + (state->homePos[botID].y - finalAngle*state->homePos[botID].x);
      }
      else 
      {
        sParam.GoToPointP.x = state->ballPos.x;
        sParam.GoToPointP.y = state->ballPos.y; 
      }
      sParam.GoToPointP.align = true;
      sParam.GoToPointP.finalVelocity = 0;
      sParam.GoToPointP.finalslope = finalAngle;
      sID = SkillSet::GoToPoint;
      skillSet->executeSkill(sID, sParam);
    }
    
	/**@return the coordinates of the opponent goalkeeper*/
    Vector2D<int> getOppGoalie()
    {
      return state->awayPos[0];
    }
  }; // class TShoot
} // namespace Strategy

#endif // TSHOOT_HPP
