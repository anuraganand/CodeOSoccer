#ifndef REF_BOX_THREAD_H
#define REF_BOX_THREAD_H

#include "thread.h"

// Forward Declarations
namespace Util
{
  class CS;
  class UDPSocket;
}

namespace HAL
{
  class RefBoxCmd;
}

namespace Strategy
{
  ///Class of Refree thread , freinds with BeliefState.
  ///@see BeliefState
  class RefBoxThread : private Util::Thread
  {
    friend class BeliefState;

  private:
    Util::UDPSocket* sock;
    HAL::RefBoxCmd*  refBoxCmdSh; ///<Shared RefBoxCommand pointer variable
    HAL::RefBoxCmd*  refBoxCmd;   ///<RefBoxCommand variable
    Util::CS*        refBoxCS;  ///<Pointer of CriticalSelection class
    static bool      instantiated;///<Boolean type.
	
	/// recieves commands from refree box 
    void run();

	public:
    /**Connects to refree box.
	 *@param refBoxCmdSh
	 *@param refBoxCS */
    RefBoxThread(HAL::RefBoxCmd* refBoxCmdSh, Util::CS* refBoxCS);
     
	 ///Destructor for refree box.
    ~RefBoxThread();
  };
}

#endif // REF_BOX_THREAD_H
