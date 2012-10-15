#ifndef TDRAGTOGOAL_HPP
#define TDRAGTOGOAL_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TDragToGoal. 
	class TDragToGoal : public Tactic
	{
	public:
	
		/**Constructor taking state and botID as param.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TDragToGoal(const BeliefState* state, int botID) :
		  Tactic(Tactic::Stop, state, botID)
		{ } 

		///Destructor.
		~TDragToGoal()
		{ }
		
		/**Checks if the tactic is of type active.
		 * @return true if active tactic*/
		inline bool isActiveTactic(void) const
		{
		  return true;
		}

		/**Returns the botID of the best bot for the given tactic among the free bots.
		 * @param freeBots list of botIDs of free bots
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
		{
		  int minv = *(freeBots.begin());
		  int mindis = 1000000000;
		  
		  /**Initially, choose bot closest to the ball as the best*/
		  for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
		  {
			float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
			if(dis_from_ball < mindis)
			{
			  mindis = dis_from_ball;
			  minv = *it;
			}
		  }
		  
		  /*If the best bot is not near the ball, choose bot for which the ball is in the wide angle range*/
		  if(mindis > 2*BOT_POINT_THRESH)
		  {
			for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
			  int bot_id = *it;
			  if(isBallInMyWideAngleRange(bot_id)) {
				minv = *it;
				break;
			  }
			}
		  }
		 printf("%d assigned DragToGoal\n", minv);
		 
		 return minv;
		}
		
		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
		  static int stt = 0;
		  Vector2D<int> fastBallPos;
		  Vector2D<float> origin(0,0);
		  fastBallPos  = Vector2D<int>((int)state->ballPos.x + 0.3*state->ballVel.x, (int)state->ballPos.y + 0.3*state->ballVel.y);
		  if(state->ballVel.absSq() > MOVING_BALL_VELOCITY*MOVING_BALL_VELOCITY) {
			Util::Logger::toStdOut("Capturing fast Ball %f\n", state->ballVel.absSq());
		  }
		  Vector2D<int> goalPoint(HALF_FIELD_MAXX, 0);
		  float theta = normalizeAngle(Vector2D<int>::angle(goalPoint, fastBallPos));
		  Vector2D<int> targetPoint = fastBallPos - Vector2D<int>(2*BOT_BALL_THRESH*cos(theta), 2*BOT_BALL_THRESH*sin(theta));
		  float sign = (state->homePos[botID].x - fastBallPos.x)*(state->homePos[botID].x - HALF_FIELD_MAXX);
		  printf("state: %d\n", stt);
		  
		  if(stt == 0 && isBallInMyWideAngleRange() && sign > 0) {
			stt = 1;
		  }
		  
		  if(stt == 1 && (!isBallInMyLastHopeRange(botID) || sign < 0)) {
			stt = 0;
		  }
		  
		  if(stt == 1)
		  {
			Util::Logger::toStdOut("Dribbling to goal %d %d", goalPoint.x, goalPoint.y);
			sID = SkillSet::GoToPoint;
			sParam.GoToPointP.finalslope = normalizeAngle(Vector2D<int>::angle( goalPoint, fastBallPos ));
			sParam.GoToPointP.x = state->ballPos.x;
			sParam.GoToPointP.y = state->ballPos.y;
			
			sParam.GoToPointP.finalVelocity = MAX_BOT_SPEED;
			sParam.GoToPointP.align = true;
			skillSet->executeSkill(sID, sParam);
		  }
		  
		  else{
			sID = SkillSet::GoToPoint;
			sParam.GoToPointP.align = true;
			sParam.GoToPointP.x = targetPoint.x;
			sParam.GoToPointP.y = targetPoint.y;
			sParam.GoToPointP.finalslope = Vector2D<int>::angle(goalPoint, state->homePos[botID]);
			sParam.GoToPointP.finalVelocity = 0.7*MAX_BOT_SPEED;
			skillSet->executeSkill(sID,sParam);
		  }
		  
		  /**Tactic completed if goal scored or if free kick or penalty awarded.*/
		  if (state->pr_oppBall || state->pr_looseBall)
		  {
			tState = COMPLETED;
		  }
		}
	  }; // class TDragToGoal 
} // namespace Strategy

#endif // TDRAGTOGOAL_HPP
