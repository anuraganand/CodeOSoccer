#ifndef TACTIC_H
#define TACTIC_H

#include <list>
#include "skillSet.h"
#include "tparamlist.h"
// Forward Declarations
namespace Strategy
{
  class BeliefState;
}

namespace HAL
{
  class Comm;
}

namespace Strategy
{
  ///Class for tactic  
  class Tactic
  {
    friend class PExec;

	public:
   ///enum for various tactics
    enum ID
    {		
      /// Defend the goal a particular distance from the goal
      Block = 0,
      ChargeBall,           /// Set-play tactic
      
      //DragToGoal,           // Go to the ball and start dragging yhe ball to goal
      //DragToGoalOpp,
      
      // Defend the ball from crossing a particular line on the field
      DefendLine,
      KickToGoal,
	  DefendPoint,          /// Defend the ball from a particular point on the field
      GoalieOur,               /// A special tactic just for the goalie for our side
      GoalieOpp,
      MarkBot,              ///Mark an opponent preventing them from getting the ball, getting to the goal, blocking a shot
      //Pass,                 /// Pass to a point
      Position,             /// Go to the given position
      PositionForPenalty,   /// Set-play tactic
      PositionForStart,     /// Set-play tactic
      Defend,                /// Defend the ball from coming to our side
      Attack,                /// Attck the ball towards the goal
      Shoot,                /// Manipulate the ball to go into the goal
      Steal,                /// Manipulate the ball to remove possession of it from another robot*/
      Stop,                 /// Stop the bot
	  Command,				/// Sends user's command directly to bot
      Velocity,             /// Move at a fixed velocity
      MAX_TACTICS,          /// Total number of tactics. All Implemented Tactics above this point
	  };

     /**Union of parameters for each tactic enumerated in Tactic::ID.
       * Creating object initializes each member by default to zero
       */
	union Param
    {
       TDefaultP            DeaultP; ///<object for TDefaultP
       TBlockP              BlockP; ///<object for TBlocktP
       TDefendLineP         DefendLineP; ///<object for TDefendP
       TPositionP           PositionP;  ///<object for TPositionP
       TPositionForStartP   PositionForStartP;  ///<object for TPositionForStartP
       TPositionForPenaltyP PositionForPenaltyP;  ///<object for TPositionFotPenaltyP
       TVelocityP           VelocityP; ///<object for TVelocityP
       TKickP               KickP;  ///<object for TDKickP
       TDefendPointP        DefendPointP;  ///<object for TDefendPointP
       TDefendP             DefendP;  ///<object for TDfendP
       TMarkBotP            MarkBotP;  ///<object for TMarkBotP
	   TCommandP			CommandP;  ///<object for TCommandP
	   TKickToGoalP			KickToGoalP;  ///<object for kick to goal
       
          /** Create a Parameter Object for Tactics
           * Initializes all the members initially to zero by default
           */
	   Param()
		{
          
          memset(this, 0, sizeof(Param) );
        }
		
        /** Create a Parameter Object for Tactics
         * Initializes all the members initially to zero by default
		 * @param tacticID a Tactic::ID type datatype
         */
		Param(Tactic::ID tacticID) {
        memset(this, 0, sizeof(Param) );
        switch(tacticID) {
          case Tactic::Block:
            this->BlockP.dist = 100;
            this->BlockP.side = 1;
            break;
          default:
            break;
        }
      }
    };
	
    /// enum for varios states of a present ongoing tactic initialised , running or completed
    enum TState
    {
      INIT,                            /// True when the tactic has just started else false
      RUNNING,                         /// True when the tactic is in the middle of execution else false
      COMPLETED                        /// True when the tactic execution is completed else false
    };

  protected:
    const Tactic::ID   tID;             ///< ID of the tactic to be executed
    const BeliefState* state;           ///< Belief State of the game
    const int          botID;           ///< ID of the bot executing this tactic
    SkillSet::SkillID  sID;             ///< ID of the skill to be executed
    SkillSet::SParam   sParam;          ///< Parameters of the selected skill to be executed
    Tactic::TState     tState;          ///< Current state of the tactic
    SkillSet*          skillSet;        ///< SkillSet object for the robot

    // TODO Remove this counter field. It is only used for debugging
    //int                counter;

	public:
    /**Constructor
	 * @param tID tactic ID
	 * @param state BeliefState type variable
	 * @param botID active bot id
	 * @see BeliefState*/
    inline Tactic(ID                 tID,
                  const BeliefState* state,
                  int                botID) :
      tID(tID),
      state(state),
      botID(botID),
      sID(SkillSet::Stop),
      tState(INIT)
      //counter(0)
    {
      skillSet = new SkillSet(state, botID);
    } // Tactic
    
    inline ~Tactic()
    {
      delete skillSet;
    } // ~Tactic

    /// True if the tactic is active, i.e., it involves ball manipulation
    virtual bool isActiveTactic(void) const = 0;
    
	///initialises tState variable
    inline void initialize(void)
    {
      tState = INIT;
    }

    // TODO As per the design, this function must be static but it cannot be both virtual as well as static
    /** This function assigns a score to all the free bots (bots that have not been
     * assigned any role yet) depending on how suitable they are in being assigned
     * the tactic. It then chooses the bot with the highest score and assigns it the tactic.
     */
    virtual int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const = 0;

    /** This function takes in the current tactic parameter for a robot and
     * using the belief state info and the skill transition rules,
     * it either decides to transit to another skill or continues to run
     * the current skill.
     */
    virtual void execute(const Param& tParam) = 0;
	
    // List utility functions for use in common in all tactics here.
	
    bool isBallInMyWideAngleRange();
    bool isBallInMyWideAngleRange(const int botID) const;
    bool isBallInMyLastHopeRange(const int botID);
	
  }; // class Tactic
} // namespace Strategy

#endif // TACTIC_H
