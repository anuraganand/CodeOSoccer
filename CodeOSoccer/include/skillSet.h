// It is through the skill layer that the Strategy layer talks to the Simulator/Actual robots

#ifndef SKILLS_H
#define SKILLS_H

#if GR_SIM_COMM
# include "grSimComm.h"
#elif SIM_COMM
# include "simComm.h"
#elif SSL_COMM
# include "sslComm.h"
#else
# error Macro for Comm class not defined
#endif

/** Forward Declarations.*/
namespace Strategy
{
  class ERRT;
  class MergeSCurve;
  class BeliefState;
}
///Template for Vector representation
template <class T> class Vector2D; 

namespace Strategy
{
  /* Procedure for adding a skill successfully to the SkillSet is:
   * 1. Enumarate it in enum SkillSet::SkillID just before MAX_SKILLS
   * 2. Identify its input parameters and define a struct for it in union SkillSet::SParam
   * 3. Declare the function prototype for the skill. Its parameter must only be SParam& param
   * 4. Map the Skill ID to the corresponding function in the constructor of SkillSet
   * 5. Define the function that implements the skill declared in step 3.
   * NOTE: Variable names of enums and corresponding skill function names must be the same,
   *       except that the enum name starts with a capital letter. Name of the corresponding
   *       struct should be the same as that of enum with a trailing 'P' character
   */
	///Class defines various skills of individual bot.
  class SkillSet
  {
	public:
	///Enum for various skills.
    enum SkillID
    {
		/**<For spin functionality as  required omega*/
		Spin ,  

      Kick,   ///< enum For skill Kick
      
	  Stop,       ///< For stopping the bot at its place
      Dribble,	  ///< For dribbling at its place
      Velocity,  ///< For defining velocity of the bot
      GoToBall,  ///< Go to the ball 
      GoToPoint,  ///< Go to specified point
      DefendPoint, ///< For defending a given point
      DribbleToPoint, ///< For taking the ball to specified point
	  KickToPoint,    ///< To hit the ball in desired direction
      ReceiveBall,   ///< For Receiving ball
      TurnToPoint,   ///< To turn to specified point
      TurnToAngle,  ///< To turn to specified angle
	  Dummy	,		///< simple parameter passing from tatic layer
      MAX_SKILLS    ///< Maximum number of available skills
	  
    };

    
    /// A union type SParam for parameters of each skill enumerated in SkillID.
	union SParam
    {
      struct
      {
        float radPerSec; ///<Stores angular velocity during spinning in radians per second.
      } SpinP;///<SpinP Parameters for the skill Spin.

		struct
			{} StopP;///<StopP For the skill Stop.
			
		
		struct
		{
			bool intercept;  /// To store wether or not to intercept he ball.*/
		}GoToBallP;///<For going to ball.
		 ///@see goToBall() .

      
      struct
      {
        float power;   ///<Power with to hit the ball.
      } KickP;///<KickP Parameters for the skill Kick.
	  
	  
	  struct
	  {
		  float power;  ///<Power with to hit the ball.
		  float x;     ///<Point x coordinate.
		  float y;     ///<Point y coordinate.
	  } KickToPointP;///<KickToPointP Parameters for the skill KickToPoint.
	  
      
      struct
      {
        float v_x;  ///<Velocity x component.
        float v_y;  ///<Velocity y component.
        float v_t;  ///< Angular Velocity component.
      } VelocityP;///<VelocityP Parameters for the skill Velocity.

      struct
      {
        float x;    ///<Point x coordinate .
        float y;    ///<Point x coordinate .
        float finalslope;	///<Final orientation of bot .
		float radius;     
      }  DefendPointP, DribbleToPointP, GoalKeepingP, TurnToAngleP, TurnToPointP;///<Parameters for skill goToPoint and dribbletopoint.
    
	
	struct
      {
        ///<Point x coordinate.
		float x;   
        float y;   ///<Point y coordinate.
        float finalslope;  ///<Final bot slope wrt to fixed ground.
		bool align;       ///<Holds wether or not to align bot to paticular angle.
		float finalVelocity;   ///<Final velocity of bot at destination point.		
      } GoToPointP;///<GoToPointP Parameters for going to a particular point.
	  
	  struct
      {
        float v_x;  /**<Velocity x component.*/
        float v_y;  /**<Velocity y component.*/
        float v_t;  /**< Angular Velocity component.*/
		float power;  /**<Power with to hit the ball.*/
		bool dribble; /**<whether dribbler is running or not.*/
      } DummyP;
	};
	
	

  private:
#if GR_SIM_COMM
    static HAL::GrSimComm comm;
#elif SIM_COMM
    static HAL::SimComm   comm;
#elif SSL_COMM
    static HAL::SSLComm   comm;
#else
#   error Macro for Comm class not defined
#endif

  protected:
    typedef void (SkillSet::*skillFncPtr)(const SParam&);
    const BeliefState* state;   ///<holds current game state parameters.
    const int          botID;   ///<Holds bot id of the bot which will perform the skill.
    skillFncPtr        skillList[MAX_SKILLS];
    MergeSCurve*       pathPlanner;  ///<Path planner.
    ERRT*              errt;        ///<ERRT

  private:
    /* trajectory2D() and trajectory1D() functions implement the path following
     * algorithm based on bang-bang motion. The pseudo code was obtained from
     * Skuba 2011 ETDP which can be found at
     * http://small-size.informatik.uni-bremen.de/tdp/etdp2011/SKUBA_ETDP_2011.pdf
     */
	 /**Function for path planner.
	  * @param startPos starting point of bot
	  * @param finalPos destination point of bot
	  * @param startVel Starting bot velocity
	  * @param fianlVel Final bot velocity
	  * @param startAng initial angular velocity
	  * @param finalAngVel bot final angular velocity
	  * @param frameRate depends on camera
	  * @param maxAcc maximum avzilable acceleration of bot
	  * @param maxAngVel maximum possible angular velocity of bot
	  * @param angVel angular velocity of the bot
	  * @param trajVel bot speed in trajectory
	  * @see ERRT*/
    void trajectory2D(const Vector2D<int>&   startPos,
                      const Vector2D<int>&   finalPos,
                      const Vector2D<float>& startVel,
                      const Vector2D<float>& finalVel,
                      const float            startAng,
                      const float            finalAng,
                      const float            startAngVel,
                      const float            finalAngVel,
                      const float            frameRate,
                      const float            maxAcc,
                      const float            maxVel,
                      const float            maxAngAcc,
                      const float            maxAngVel,
                      Vector2D<float>&       trajVel,
                      float&                 angVel);

    /* Given the distance to cover, start velocity, final velocity,
     * frame rate, maximum acceleration and maximum velocity, this function
     * computes the required initial acceleration and the time required
     * to complete the path and returns it. In case, a path is not feasible
     * with the given values, a very high value of time for completing the 
     * path is returned
     */
	 /**Function for path planner.
	  * @param dist 
	  * @param startVel Starting bot velocity
	  * @param fianlVel Final bot velocity
	  * @param frameRate depends on camera
	  * @param maxAcc maximum available acceleration of bot
	  * @param maxVel maximum possible velocity of bot
	  * @param trajAcc 
	  * @param trajTime
	  * @see ERRT*/
    void trajectory1D(const float dist,
                      const float startVel,
                      const float finalVel,
                      const float frameRate,
                      const float maxAcc,
                      const float maxVel,
                      float&      trajAcc,
                      float&      tracTime);

  public:
    //------- List of robot skills -------//
	/**Function for bot spinning.
	 * @param param constant variable of structure type SpinP within union SParam 
	 * @see SParam
	 * @see SpinP*/	 
    void spin(const SParam& param);
	
	/**Function for bot stopping.
	 * @param param constant variable of structure type StopP within union SParam 
	 * @see SParam
	 * @see StopP*/
    void stop(const SParam& param);
	
	/**Function for bot kicking.
	 * @param param constant variable of structure type KickP within union SParam 
	 * @see SParam
	 * @see KickP*/
    void kick(const SParam& param);
	
	/**Function for bot stopping.
	 * @param param constant variable of structure type DribbleP within union SParam 
	 * @see SParam
	 * @see DribbleP*/
    void dribble(const SParam& param);
	
    /**Function for bot moving veocity.
	 * @param param constant variable of structure type VelocityP within union SParam 
	 * @see SParam
	 * @see VelocityP*/
	void velocity(const SParam& param);
	
	/**Function for direct parameter passing.
	 * @param param constant variable of structure type VelocityP within union SParam 
	 * @see SParam
	 * @see DummyyP*/
	void dummy(const SParam& param);
	
	/**Function for reachig the ball.
	 * @param param constant variable of structure type GoToBallP within union SParam 
	 * @see SParam
	 * @see GoToBallP*/
    void goToBall(const SParam& param);
	
	/**Function for bot goint to a given point.
	 * @param param constant variable of structure type GoToPointP within union SParam 
	 * @see SParam
	 * @see GoToPointP*/
    void goToPoint(const SParam& param);

     /**Function for defending point.
	 * @param param constant variable of structure type DefendPointP within union SParam 
	 * @see SParam
	 * @see DefendPointP*/
    void defendPoint(const SParam& param);
	
	/**Function for dribbling to a specied point.
	 * @param param constant variable of structure type DribbleToPointP within union SParam 
	 * @see SParam
	 * @see DribbleToPointP*/
    void dribbleToPoint(const SParam& param);
	
	/**Function for receiving tha ball.
	 * @param param constant variable of structure type ReceiveBallP within union SParam 
	 * @see SParam*/
    void receiveBall(const SParam& param);
	
	/**Function for goalKeeping.
	 * @param param constant variable of structure type GoalKeepingP within union SParam 
	 * @see SParam
	 * @see GoalKeepingP*/
    void goalKeeping(SParam& param);
	
	/**Function for bot kicking to a point.
	 * @param param constant variable of structure type KickToPointP within union SParam 
	 * @see SParam
	 * @see KickToPointP*/
	void kickToPoint(const SParam& param);

	/**Function for bot turning to specified angle.
	 * @param param constant variable of structure type TurnToAngleP within union SParam 
	 * @see SParam
	 * @see TurnToAngleP*/   
    void turnToAngle(const SParam& param);
	
	/**Function for bot turning to specified angle.
	 * @param param constant variable of structure type TurnToPointP within union SParam 
	 * @see SParam
	 * @see TurnToPointP*/ 
	void turnToPoint(const SParam& param);

    /**Constructor of SkillSet.
	 * @param state constant BeliefState type variable
	 * @param botID integer type varible for assigining bot id
	 * @see BeliefState*/
	SkillSet(const BeliefState* state, int botID);
     
	 /**Destructor*/
    ~SkillSet();

    /** Executing the skill function corresponding to the given ID and param function parameters.
	 * @param ID variable of type SkillID to hold id of current bot
	 * @param param a variable of union type
	 * @see SParam*/
    inline void executeSkill(SkillID ID, const SParam& param)
    {
      (*this.*skillList[ID])(param);
    } // executeSkill
  }; // class SkillSet
} // namespace Strategy

#endif // SKILLS_H
