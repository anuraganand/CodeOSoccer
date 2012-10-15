#ifndef TCHARGE_HPP
#define TCHARGE_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TCharge. 
  class TCharge : public Tactic
  {
		public:
			
		/**Constructor taking state and botID as parameters.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TCharge(const BeliefState* state, int botID) :
		  Tactic(Tactic::Stop, state, botID)
		{ }

		/**Destructor.*/
		~TCharge()
		{ }

		/**Checks if the tactic is of type active.*/
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
		  Util::Logger::toStdOut("Selected bot %d\n", minv);
		  return minv;			/**The best bot for the tactic is the one closest to the ball. */
		} 
		
		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
			/**Dribbles to the opponent's goal if the ball with our bot.
			 * @see BeliefState */
			 printf("%d\n",state->pr_ourBall);
			if(state->pr_ourBall)
			{	
				sID = SkillSet::DribbleToPoint;
				sParam.DribbleToPointP.x=HALF_FIELD_MAXX;
				sParam.DribbleToPointP.y=(OPP_GOAL_MAXY+OPP_GOAL_MINY)/2;
				skillSet->executeSkill(sID, sParam);
			}
			
			/**Goes to the ball if it is not in our possession.
			 * @see BeliefState */
			else if(state->pr_oppBall || state->pr_looseBall)
			{
				sID=SkillSet::GoToBall;
				sParam.GoToBallP.intercept=false;
				skillSet->executeSkill(sID,sParam);
			}
		
			/**Tactic completed if goal scored.*/
			if (state->pr_goalscored)
				tState = COMPLETED;
			else
				tState = RUNNING;
		}
	}; /// class TCharge
} // namespace Strategy
#endif // TCHARGE_HPP
