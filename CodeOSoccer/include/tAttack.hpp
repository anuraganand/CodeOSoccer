#ifndef TATTACK_HPP
#define TATTACK_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
  ///class for Attack tactic
	class TAttack : public Tactic
  {
	public:
    /**constructor
	 * @param state BeliefState type variable
	 * @param botID player bot ID
	 * @see BeliefState*/
    TAttack(const BeliefState* state, int botID) :
      Tactic(Tactic::Attack, state, botID)
    { iState = APPROACHING; } // TAttack
     
	 ///Destructor
    ~TAttack()
    { } // ~TAttack
	
	///enum for internal state
    enum InternalState
    {
      APPROACHING,
      SPINNING_CCW=-1,
      SPINNING_CW=1,      
      ATTACKING
    }iState; 
	
	/**@return boolean type*/
    inline bool isActiveTactic(void) const
    {
      return true;
    }
    /**@return botID of the most suitable bot
	*@param std::list<int>& freeBots
	* @param tParam Tactic::Param* type*/
    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
      int minv = *(freeBots.begin());
      int mindis = (state->homePos[*(freeBots.begin())] - state->ballPos).absSq();
      for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
      {
        float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
        if(*it == botID)
          dis_from_ball -=HYSTERESIS;
        if(dis_from_ball < mindis)
        {
          dis_from_ball = mindis;
          minv = *it;
        }
      }
      Util::Logger::toStdOut("Selected bot %d\n", minv);
      return minv;
      
    } // chooseBestBot

    
    bool pointxInField(Vector2D<int> final)
    {
      if((final.x < HALF_FIELD_MAXX + (BALL_AT_CORNER_THRESH)/*||final.x<-HALF_FIELD_MAXX-(BALL_AT_CORNER_THRESH))*/))
      {
        if((final.y < OPP_GOAL_MINY||final.y > OPP_GOAL_MAXY))
        {
          return false;
        }
        else return true;
      }
      else  return true;
    }
	/**@param tParam parameter for Tactics
	 * function to perform the required tactic*/
    void execute(const Param& tParam)
    {
      float dist = Vector2D<int>::dist(state->ballPos,state->homePos[botID]);
      if(!pointxInField(state->ballPos))
      {
        printf("---------------------------My Code\n");
        if(dist < BOT_BALL_THRESH/2)
        {
          sID=SkillSet::Spin;
          sParam.SpinP.radPerSec=MAX_BOT_OMEGA;
          skillSet->executeSkill(sID,sParam);
          printf("SPIN\n");
        }
        else
        {
          if(state->ballPos.y>0)
          {
            sID = SkillSet::GoToPoint;
            sParam.GoToPointP.align = true;
            sParam.GoToPointP.x = state->ballPos.x;
            sParam.GoToPointP.y = state->ballPos.y;
            skillSet->executeSkill(sID,sParam);
          }
          else
          {
            sID = SkillSet::GoToPoint;
            sParam.GoToPointP.align = true;
            sParam.GoToPointP.x = state->ballPos.x;
            sParam.GoToPointP.y = state->ballPos.y;
            skillSet->executeSkill(sID,sParam);
          }
        }
      }
      else
      {    
        if(iState == SPINNING_CW || iState == SPINNING_CCW)
        {
          if(dist > BOT_BALL_THRESH*1.2)
          {
            iState = APPROACHING;
          }
          else
          {
          sID = SkillSet::Spin;
          if(iState == SPINNING_CW)
            sParam.SpinP.radPerSec = MAX_BOT_OMEGA;
          else
            sParam.SpinP.radPerSec = -MAX_BOT_OMEGA;
          skillSet->executeSkill(sID, sParam);
          return;
          }
        }
        if(dist < BOT_BALL_THRESH)
        {
          if(fabs(normalizeAngle(state->homeAngle[botID] - atan2(state->homePos[botID].y - state->ballPos.y, state->homePos[botID].x - state->ballPos.x))) < PI/2 + PI/10 && fabs(normalizeAngle(state->homeAngle[botID] - atan2(state->homePos[botID].y - state->ballPos.y, state->homePos[botID].x - state->ballPos.x)))  > PI/2 - PI/10)
          {
            if(state->ballPos.y>0)
              iState = SPINNING_CW;
            else
              iState = SPINNING_CCW;
          }
          else
          {
          sID = SkillSet::GoToPoint;
          sParam.GoToPointP.align = true;
          sParam.GoToPointP.x = HALF_FIELD_MAXX;
          sParam.GoToPointP.y = 0;
          sParam.GoToPointP.finalslope = Vector2D<int>::angle(Vector2D<int>(HALF_FIELD_MAXX,0),state->ballPos);
          skillSet->executeSkill(sID,sParam);
          tState = RUNNING;
          iState = ATTACKING;
          }
        }
        else
        {
          if(state->pr_ourBall)
          {
			  
          }
		  
          sID = SkillSet::GoToPoint;
          sParam.GoToPointP.align = true;
          sParam.GoToPointP.x = state->ballPos.x;
          sParam.GoToPointP.y = state->ballPos.y;
          sParam.GoToPointP.finalslope = Vector2D<int>::angle(Vector2D<int>(HALF_FIELD_MAXX,0),state->ballPos);
          skillSet->executeSkill(sID,sParam);
        }
      }
    }
  }; // class TAttack
} // namespace Strategy

#endif // TATTACK_HPP
