#ifndef TGOALKEEPINGOUR_HPP
#define TGOALKEEPINGOUR_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"
#include "geometry.hpp"
#define GOAL_Y 0
#define AWAYGOAL_X HALF_FIELD_MAXX

namespace Strategy
{
	///Class for Tactic TGoalKeepingOurSide. 
	class TGoalKeepingOurSide : public Tactic
	{
		public:
			int state1;
			
			/**Constructor taking state and botID as param.
			*@param state a belief state type variable
			*@param botID an integer which identifies the bot executing the tactic
			*@see BeliefState*/
			TGoalKeepingOurSide(const BeliefState* state, int botID) :
				Tactic(Tactic::Stop, state, botID)
			{
				state1 = 0;
			} 
			
			///Destructor.
			~TGoalKeepingOurSide()
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
				int mindis = 1000000000;
				Point2D<int> goalPos(-(HALF_FIELD_MAXX),0);
				for(std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
				{
					float dis_from_goal = (state->homePos[*it] - goalPos).absSq();
					if(dis_from_goal < mindis)
					{
						mindis = dis_from_goal;
						minv = *it;
					}
				}
				printf("%d assigned Goalie\n", minv);
				return minv;	/**The best bot for the tactic is the one closest to the goal. */
			}

			/**Checks if the goalkeeper is inside the penalty area.
			 * @return true if goalkeeper is in position*/
			bool isGoalKeeperInPosition()
			{
				if((state->homePos[botID].x > -HALF_FIELD_MAXX) &&
					(state->homePos[botID].x <= -HALF_FIELD_MAXX + DBOX_WIDTH) &&
				    (state->homePos[botID].y >= OUR_GOAL_MINY) &&
				    (state->homePos[botID].y <= OUR_GOAL_MAXY))
					return true;
				else
					return false;

			}

			/**Calculates the destination point for the goalkeeper.
			 * @return int type*/
			int getBotDestPointY()
			{
				Vector2D<int> ballFinalpos, botDestination, point;
				ballFinalpos.x = state->ballPos.x+state->ballVel.x;
				ballFinalpos.y = state->ballPos.y+state->ballVel.y;
				botDestination.x=-(HALF_FIELD_MAXX)+DBOX_WIDTH/4;
				
				/* Workaround for ball velocity 0*/
				if(fabs(ballFinalpos.y - state->ballPos.y)<5 || fabs(ballFinalpos.x - state->ballPos.x)<5)
				{
					point.y = state->ballPos.y;
				}
				else
				{
					botDestination.y = (ballFinalpos.y - state->ballPos.y)/(ballFinalpos.x - state->ballPos.x)*(botDestination.x - ballFinalpos.x) + ballFinalpos.y;
					point.y = botDestination.y;
				}
				
				/* Set Limits on y to not exceed penalty area's bounds*/
				if(point.y<OUR_GOAL_MINY)
					point.y = OUR_GOAL_MINY + BOT_RADIUS;
				else if(point.y>OUR_GOAL_MAXY)
					point.y = OUR_GOAL_MAXY - BOT_RADIUS;

				return point.y;
			}
			
			/**Executes tactic with given Tactic parameters.
			 * @param tParam tactic parameters
			 * @see Tactic::Param*/
			void execute(const Param& tParam)
			{
				/**If goalkeeper is not in penalty area, bring it there.*/
				if(!isGoalKeeperInPosition())
				{
					sID = SkillSet::GoToPoint;
					sParam.GoToPointP.align = false;
					sParam.GoToPointP.finalslope = PI/2;
					sParam.GoToPointP.x=-(HALF_FIELD_MAXX)+DBOX_WIDTH/4;
					sParam.GoToPointP.y=(OUR_GOAL_MAXY+OUR_GOAL_MINY)/2;
					skillSet->executeSkill(sID, sParam);
				}
				
				/**If goalkeeper is in penalty area, go to calculated destination point.*/
				else
				{
					state1 =1 ;
					sID = SkillSet::GoToPoint;
					sParam.GoToPointP.x = -(HALF_FIELD_MAXX)+DBOX_WIDTH/4;
					sParam.GoToPointP.y = getBotDestPointY();
					sParam.GoToPointP.finalslope = atan2(state->homePos[botID].y-state->ballPos.y,state->homePos[botID].y-state->ballPos.x);

					sParam.GoToPointP.align = true;
					skillSet->executeSkill(sID, sParam);
				}
			tState = COMPLETED;
			}
	} ; // class TGoalKeepingOurSide 
} // namespace Strategy

#endif // TGOALKEEPINGOUR_HPP

