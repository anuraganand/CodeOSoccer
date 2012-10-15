#ifndef TMARKBOT_HPP	
#define TMARKBOT_HPP

#define BOT_DIS_THRESH 0.5 
#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TMarkBot. 
	class TMarkBot : public Tactic
	{
	public:
		
		/**Constructor taking state and botID as parameters.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TMarkBot(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ } 
		
		/**Destructor.*/
		~TMarkBot()
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
			int mindis = 10000;
			for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				float dis_from_bot = (state->homePos[*it] - state->awayPos[*it]).absSq();
				if(dis_from_bot < mindis)
				{
					dis_from_bot = mindis;
					minv = *it;
				}
			}
			return minv; /**The best bot for the tactic is the one closest to the bot to be marked.*/
		} 

		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
			/**Defends the location of the bot to be marked*/
           sParam.DefendPointP.x=state->awayPos[tParam.MarkBotP.awayBotID].x;
           sParam.DefendPointP.y=state->awayPos[tParam.MarkBotP.awayBotID].y;
           sID = SkillSet::DefendPoint ;
		   skillSet->executeSkill(sID, sParam);
      
			/**Tactic completed if bot reaches the bot to be marked.*/
			if ((state->homePos[botID] - state->awayPos[botID]).absSq() < BOT_DIS_THRESH * BOT_DIS_THRESH)
			{
				tState = COMPLETED;
			}
		}
	}; // class TMarkBot
} // namespace Strategy

#endif // TMARKBOT_HPP