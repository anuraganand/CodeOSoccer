#ifndef TPASS_HPP
#define TPASS_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TPass.
	class TPass : public Tactic
	{
	public:
	
		///Constructor taking state and botID as parameters.
		///@param state a belief state type variable
		///@param botID an integer which identifies the bot executing the tactic
		///@see BeliefState
		TPass(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ }

		///Destructor.
		~TPass()
		{ }

		/**Checks if the tactic is of type active.*/
		inline bool isActiveTactic(void) const
		{
			return true;
		}
    
		/**Returns the botID of the best bot for the given tactic among the free bots.
		 * @param freeBots list of botIDs of free bots
		 * @param tParam tactic parameters
		 * @see Tactic::Param
		 * @return The best bot for the tactic is the one closest to the ball. */
		int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
		{
			int minv = *(freeBots.begin());
			int mindis = Vector2D<int>::dist(state->homePos[minv],state->ballPos);
			for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				if(Vector2D<int>::dist(state->homePos[*it],state->ballPos)<mindis)
				{
					mindis = Vector2D<int>::dist(state->homePos[*it],state->ballPos);;
					minv = *it;
				}
			}
			return minv;
		} 
		
		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
			/**Kicks the ball to the point where it has to be passed.*/
			sID = SkillSet::KickToPoint;
			sParam.KickToPointP.x = tParam.PassP.x;
			sParam.KickToPointP.y = tParam.PassP.y;
			sParam.KickToPointP.power = tParam.PassP.power;
			skillSet->executeSkill(sID, sParam); 

			/**Tactic completed if bot is close to ball.*/
			if (state->homePos[botID].absSq() < BOT_BALL_THRESH * BOT_BALL_THRESH)   
			{
				tState = COMPLETED;
			}			
		}
	}; // class TPass
} // namespace Strategy

#endif // TPass_HPP
