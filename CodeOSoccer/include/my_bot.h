#ifndef MYBOT_H
#define MYBOT_H
#include "tactic.h"
#include "mainheaders.hpp"
#define SEND_COMMAND(botid, vx, vy, vt, kick, dribble) comm.sendCommand(botID, 0, 0, 0, 0, true);
#define BOT_COUNT 5
namespace Strategy 
{
  /**@class MyBot Class for our bot.*/ 
  class MyBot {
  public:
    BeliefState *state; /**<Pointer of class BeliefState .
                        * Has the paramteres and functionalities for current game state
                        *@see BeliefState  */
    /**Constructor taking state as param.
    *@param state a belief state type variable
    *@see BeliefState*/
    MyBot(BeliefState *state);
	
    /**Destructor.*/
    ~MyBot();
  
    Tactic* tacticList[5][Tactic::MAX_TACTICS]; /**<2-D lists tactics for each bot*/
  
    /**Function Prototype for running Bot.*/
    void _run_bot();
	
    /**Function for tactic execution for a bot.
     * @param botid to hold player id
     * @param tacticId to hold id of tactic to run
     * @param param holds the required parameters for tactic execution*/
      void executeTactic(int botid, Tactic::ID tacticId, Tactic::Param param);
    /**Updates the beliefstate variable.
    * @see BeliefState*/
    void update();
  };
}
#endif // MYBOT_H
