#ifndef VISION_THREAD_H
#define VISION_THREAD_H

#include "thread.h"
#include "client.h"

/// Forward Declarations
namespace HAL
{
  class VisionInfo;
}

namespace Util
{
  class CS;
}

namespace Strategy
{
  class Kalman;
}

namespace Strategy
{
   ///Class of VisionThread
	class VisionThread : public Util::Thread
  {

  private:
    SSL_WrapperPacket recvPacket;  ///<Object of Wrapper class , involved in recieveing frmes from SSLVision
    static bool       instantiated; ///<Boolean type variable
    Kalman*           kFilter; ///<Kalman filter pointer
    Simulator::Client client; /**<Object of Client .
	                           *@see Client*/ 
	
    void run();

	public:
  /**Constructor for VisionThread
   * @param kFilter object of class Kalman*/
    VisionThread(Kalman& kFilter);
	///Destructor for VisionThread
    ~VisionThread();
  }; // class VisionThread
} // namespace Strategy

#endif  // VISION_THREAD_H
