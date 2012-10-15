#ifndef TBLOCK_HPP
#define TBLOCK_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TBlock. 
	class TBlock : public Tactic
	{
	public:
		/**Constructor taking state and botID as parameters.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TBlock(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ } 
		
		/**Destructor.*/
		~TBlock()
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
			int mindis = Vector2D<int>::dist(state->homePos[minv],state->ballPos);
			for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				if(Vector2D<int>::dist(state->homePos[*it],state->ballPos)<mindis)
				{
					mindis = Vector2D<int>::dist(state->homePos[*it],state->ballPos);;
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
		    sID = SkillSet::GoToPoint;
		    sParam.GoToPointP.x=state->ballPos.x + tParam.BlockP.dist; /**set GoToPoint parameters according to blocking side and distance from ball.*/
		    sParam.GoToPointP.y=state->ballPos.y + tParam.BlockP.side*tParam.BlockP.dist;
		    
		    skillSet->executeSkill(sID, sParam); /**Executes the skill GoToPoint with calculated parameters.*/
		    
		    /**Tactic completed when bot is in opponent's penalty area.*/
        
		    if(state->homePos[botID].x>OPP_D)
		    {
			  sID = SkillSet::Stop;
			  printf("Competed Tactic\n");
			  tState = COMPLETED; 
		    }
		}
	}; // class Tblock
} // namespace Strategy

#endif // TBLOCK_HPP
