/* This header file contains the definition of
 * class SimComm  which inherits Comm class.
 * This class is used to  assign commands to the all
 * the bots of the team - v_x, v_y, v_t, kickpower, dribble
 */

#ifndef SIM_COMM_H
#define SIM_COMM_H

#include "comm.h"
#include "rbCommDef.h"

// Forward Declarations
namespace Util
{
  class Shmem;
  class CS;
}

namespace HAL
{
  class SimComm : public Comm
  {
  private:
    Util::Shmem* shmem;
    SimPacket    command;

  public:
    SimComm();

    ~SimComm();

    void sendDebugInfo(const CanvasItem* items, int numItems);
		
	/**Sends commands to bot in GR simulator. Takes parameters 
	  * @param botID : bot number(0/1/2) to which commands have to be sent
	  * @param v_x : velocity in x direction wrt bot. ie in direction of bot.
	  * @param v_y : velocity in y direction wrt bot. ie perpendicular to direction of bot.
	  * @param v_t : rotational velocity.In rad/sec.
	  * @param kickPower : Power with which kicker kicks. In range [0,1].
	  * @param dribble : whether dribbler should be on or off.
	  */
    void sendCommand(int   botID,
                     float v_x,
                     float v_y,
                     float v_t,
                     float kickPower,
                     bool  dribble);
  };
}

#endif // SIM_COMM_H
