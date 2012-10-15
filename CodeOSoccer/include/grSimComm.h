/* This header file contains the definition of class SimComm  which inherits Comm class.
 * This class is used to  assign commands to the all the bots of the team for the 3D simulator.
 */

#ifndef SIM3D_COMM_H
#define SIM3D_COMM_H

#include <list>
#include "comm.h"
#include "netraw.h"
#include "sslDebug_Data.pb.h"

// Forward Declarations
namespace Util
{
  class CS;
}

namespace HAL
{
  class GrSimComm : public Comm
  {
  private:
    Net::UDP                udpsocket;
    Net::Address            _addr;
    std::list<Debug_Circle> debug_circles;
    std::list<Debug_Line>   debug_lines;
    
    bool reconnectUDP();
    void disconnectUDP();

  public:
    GrSimComm();

    ~GrSimComm();

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
     /**Adds a circle in simulator at @param x, @param y of radius @param radius*/                
    inline void addCircle(int x, int y, unsigned int radius)
    {
      Debug_Circle circle;
      circle.set_x(x);
      circle.set_y(y);
      circle.set_radius(radius);
      debug_circles.push_back(circle);
    }
    /**Adds a straight line in simulator from @param x1, @param y1 to @param x2, @param y2 */      
    inline void addLine(int x1, int y1, int x2, int y2)
    {
      Debug_Line line;
      line.set_x1(x1);
      line.set_y1(y1);
      line.set_x2(x2);
      line.set_y2(y2);
      debug_lines.push_back(line);
    }
  };
}

#endif // SIM3D_COMM_H
