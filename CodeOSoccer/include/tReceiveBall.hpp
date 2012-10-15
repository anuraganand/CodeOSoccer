#ifndef TRECEIVEBALL_HPP
#define TRECEIVEBALL_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TReceiveBall. 
	class TReceiveBall: public Tactic
	{
		public:
		
		/**Constructor taking state and botID as parameters.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TReceiveBall(const BeliefState* state, int botID) :
				Tactic(Tactic::Stop, state, botID)
		{ }
		
		/**Destructor.*/
		~TReceiveBall()
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
			int minv = *(freeBots.begin());
			int mindis = 10000;
			for(std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
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
			Vector2D<float> homePosfloat;
			homePosfloat.x = state->homePos[botID].x;
			homePosfloat.y = state->homePos[botID].y;
			float dist = Vector2D<int>::dist(state->ballPos, state->homePos[botID]);
			float angle = normalizeAngle(Vector2D<float>::angle(state->ballVel, homePosfloat));   //angle between ball's predicted path and bot position
			Vector2D<float> target = state->ballVel/((state->ballVel).abs());
			target = target*(dist*cos(angle));
			/**Goes to the target point if ball is  free.
			 * @see BeliefState */
			if(state->pr_looseBall)
			{
				sID=SkillSet::GoToPoint;
				sParam.GoToPointP.x=target.x;
				sParam.GoToPointP.y=target.y;
				sParam.GoToPointP.align=true;
				skillSet->executeSkill(sID,sParam);
			}
			/**Tactic completed if ball is in our possession or opponent's possession aur goal scored.
			 * @see BeliefState */
			if(state->pr_goalscored || state->pr_ourBall || state->pr_oppBall)
				tState = COMPLETED;
			else
				tState = RUNNING;
		}
} ;// class TReceiveBall
} // namespace Strategy
#endif // TRECEIVEBALL_HPP