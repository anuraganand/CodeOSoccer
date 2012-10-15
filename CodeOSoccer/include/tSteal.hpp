#ifndef TSTEAL_HPP
#define TSTEAL_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TSteal. 
	class TSteal : public Tactic
	{
	public:
		
		/**Constructor taking state and botID as parameters.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TSteal(const BeliefState* state, int botID) :Tactic(Tactic::Stop, state, botID)
		{ } 

        ///Destructor.
		~TSteal()
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
			for(std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				float dis_from_opp = (state->homePos[*it] - state->awayPos[state->oppBotNearestToBall]).absSq();
				if(*it == botID)
						dis_from_opp-=HYSTERESIS;
				if(dis_from_opp < mindis)
				{
					mindis = dis_from_opp;
					minv = *it;
				}
			}
			printf("%d assigned Steal\n", minv);
			return minv; /**The best bot for the tactic is the one closest to the opponent which has the ball. */
		} 
		
		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
			/**Goes to the ball if it is free.
			 * @see BeliefState */
			if(state->pr_looseBall == true)
			{
				printf("LOOSE BALL\n");
				sID = SkillSet::GoToBall;
				skillSet->executeSkill(sID, sParam);
				tState = RUNNING;
				if(Vector2D<int>::dist(state->ballPos,state->homePos[botID])<DRIBBLER_BALL_THRESH)   //
				{
						printf("BALL CAPTURED\n");
						sID = SkillSet::Dribble;
						skillSet->executeSkill(sID, sParam);
						tState = COMPLETED;
				}
				//Util::Logger::toStdOut("Going to  : %f,%f\n",sParam.GoToPointP.x,sParam.GoToPointP.y);
			}
			/**If ball is with opponent goes to the ball and turn by PI/2.
			 * @see BeliefState */
			if(state->pr_oppBall == true)
			{
				printf("OPP BALL\n");
				sID = SkillSet::GoToBall;
				skillSet->executeSkill(sID, sParam);
				tState = RUNNING;
				if(Vector2D<int>::dist(state->ballPos,state->homePos[botID])<DRIBBLER_BALL_THRESH)
				{
						printf("BALL CAPTURED , NOW TURNING WITH BALL\n");
						sID=SkillSet::TurnToAngle;
						float finalincline=state->homeAngle[botID]+PI/2;
						while((finalincline-state->homeAngle[botID])>0.5)     // to turn the bot once taken away from oppenent
						{
								sParam.TurnToAngleP.finalslope=finalincline;
								skillSet->executeSkill(sID, sParam);
						}
						tState = COMPLETED;
				}
			}
			
			/**Tactic completed if possession gained.*/
			if(state->pr_ourBall == true)
			{
				printf("OUR BALL\n");
				tState = COMPLETED;
				sID = SkillSet::Stop;
				skillSet->executeSkill(sID, sParam);
			}
		}
	}; // class TSteal
} // namespace Strategy

#endif // TSTEAL_HPP