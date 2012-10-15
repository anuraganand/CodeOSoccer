#ifndef ROBOT_H
#define ROBOT_H

#include "thread.h"
#include "tactic.h"

/**Forward Declarations.*/
namespace Util
{
  class CS;
}
/**Forward Declarations.*/
namespace Strategy
{
  class BeliefState;
}

namespace Strategy
{
  /**@class Robot It declares class PExec as its friend.*/
  class Robot : private Util::Thread
  {
    friend class PExec;

  public:
    Tactic::ID     tIDSh; /**<Stores the current tactic and is controlled by the Play Layer.*/
    Tactic::Param  tParamSh; /**<Stores the current tactic's parameters and is controlled by the Play Layer.*/
    Tactic::TState tStateSh; /**<Stores the current tactic's state and is controlled by the Play Layer.*/
    Tactic*        tacticList[Tactic::MAX_TACTICS]; /**<List of tactics: A map of ID -> Tactic objects.*/

  private:
    int            botID;  /**<Private int type variale to hold bot ID.*/

    Util::CS*      tacticCS;/**<Critical Section object for synchronizing access to the above two fields.*/
    
    BeliefState*   state;/**<BeliefState object the bot will use.
	                     *@see BeliefState */
    
    BeliefState&   stateSh;/**<hared Belief State object between it and the main thread.*/
    
    Util::CS&      stateCS;/**<Critical Section object for synchronizing access to the belief state.*/

    /**The function in which the Tactic loop runs forever.*/
    void run();

	public:
   /**Constructor for class Robot.
    * @param stateSh
	* @param stateCS
	* @param tacticCS
	* @param botID
	* @see stateSh
	* @see stateCS
	* @see tacticCS
	* @see botID*/
    Robot(BeliefState& stateSh,
          Util::CS&    stateCS,
          Util::CS*    tacticCS,
          int          botID);

 /**Destructor for class Robot*/
    ~Robot();
  }; // class Robot
} // namespace Strategy

#endif // ROBOT_H
