#ifndef PLAY_BOOK_H
#define PLAY_BOOK_H

/** Forward Declarations.*/
namespace Strategy
{
  class BeliefState;
  class Play;
}

namespace Strategy
{
  /**@class Playbook It handles the plays.*/
  class PlayBook
  {
  public:
 /**@enum PlayID Enum for various types of plays. */
    enum PlayID
    {
      TestPlay, /**<Test play for bot testing.*/
      /* Position Plays*/
      SetPosition,  /**<Play to set positions of team members initially.*/
      PositionOurStrike, /**<Play to position team members when its our strike.*/
      PositionOppStrike,/**<Play to position team members when its oupposition strike.*/
      OffenceSetPosition1,   /**<Position set Play to be used when we in offence mode.*/
      DefenceSetPosition1,  /**<Position set Play to be used when we in defence mode.*/
      None,
      /* General Plays During Match .*/
      OffensePlay,      /**<Play to be used while we are attacking and offensive.*/
      DefensiveGoToGoal, /**<Play to be used in ou defence mode.*/
      DefensiveSteal,  /**<Play to steal the ball from opponent to get possession.*/
      /* Specific Case Plays - FreeKick,Penalty .*/
      OurGoalKick,   /**<Used in our goal kick.*/
      OppGoalKick,   /**Used in opponent goal kick.*/
      TieBreakerOurPenalty,  /**<Our penalty in tiebreaker.*/
      TieBreakerOppPenalty,  /**<Opponent penalty in tiebreaker.*/
      MAX_PLAYS   /**<holds maximum number of plays.*/
    };

  protected:
    const BeliefState& state; /**<Constant type BeliefState variable holding current game state.
                              *@see BeliefState*/

    Play*              playList[MAX_PLAYS];  /**<PlayList for all plays.*/

  public:
   /**Constructor for PlayBook class.
   *@param state BeliefState type variable
   *@see state*/
    PlayBook(const BeliefState& state);
    
    /**Destructor for class PlayBook.*/
    ~PlayBook();

    /**Function that reloads plays.
    *Initializes all play objects with null then readefines them*/
    void reload(void);
  }; // class PlayBook
} // namespace Strategy

#endif // PLAY_BOOK_H
