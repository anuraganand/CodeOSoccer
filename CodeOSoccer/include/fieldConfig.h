#ifndef FIELD_CONFIG_H
#define FIELD_CONFIG_H


#if SIM_COMM || GR_SIM_COMM // Parameters for the simulator
# define SELECT(sim_param, ssl_param) (sim_param)
#elif SSL_COMM || FIRA_COMM// Parametres for the real bots
# define SELECT(sim_param, ssl_param) (ssl_param)
#else
# error Macro for Comm class not fully handled
#endif
#define SGN(x) (((x)>0)?1:(((x)<0)?(-1):0))

extern bool FIELD_IS_INVERTED; /**<Bollean type global variable .
                               *True when to invert the field i.e. side change  */
							   
/**Template for distance varible sign correction in inverted field.
 * @param distance template variable of any suitable type
 * @return returns only magnitude of distance*/
template <typename T> T ForwardX(T distance) {
  return FIELD_IS_INVERTED?(-distance):(distance);
}
#define SELECTX(a, b) ForwardX(SELECT(a, b))

static const float MOVING_BALL_VELOCITY       = SELECT(40, 30); /**<constant float type static variable in mm.
                                                                 *holds velocity of moving ball
															     *first value for simulator , second value for ssl vision */
static const float MIN_DIST_FROM_TARGET       = SELECT(30.0, 25.0);/**<constant float type static variable in mm.
                                                                 *holds minimum distance from the target
															     *first value for simulator , second value for ssl vision */
static const int CENTER_X                     = SELECT(0, 257);/**<constant int type static variable in mm.
                                                                 *holds x coordinate of field centre
															     *first value for simulator , second value for ssl vision */

static const int CENTER_Y                     = SELECT(0, 236);/**<constant int type static variable.
                                                                 *holds y coordinate of field centre in mm
															     *first value for simulator , second value for ssl vision */
static const int HALF_FIELD_MAXX              = SELECTX(3025, 202); /**<constant int type static variable.
                                                                 *holds maximum positive x , half field length in mm
															     *first value for simulator , second value for ssl vision */
																 //actual 225 (rugged surface at end)

static const int HALF_FIELD_MAXY              = SELECT(2025, 200);/**<constant int type static variable.
                                                                 *holds maximum positive y , half field width in mm
															     *first value for simulator , second value for ssl vision */
																 
static const int OUR_GOAL_MAXY                = SELECT(400, 70);/**<constant int type static variable.						
																  *holds maximum positive y for our goal post in mm	
														          * first value for simulator , second value for ssl vision */
																  
static const int OUR_GOAL_MINY                = SELECT(-400, -70);/**<constant int type static variable.						
																  *holds y coordinate of our second goal post pole in mm
																 *first value for simulator , second value for ssl vision */

static const int OPP_GOAL_MAXY                = SELECT(400, 30);/**<constant int type static variable.						
																  *holds positive y coordinate of opponent goal post pole in mm
																 *first value for simulator , second value for ssl vision */
																 
static const int OPP_GOAL_MINY                = SELECT(-400, -30);/**<constant int type static variable.						
																  *holds negative y coordinate of opponent second pole of goal post in mm
																 *first value for simulator , second value for ssl vision */
																 
static const int OUR_GOAL_WIDTH               = OUR_GOAL_MAXY - OUR_GOAL_MINY;/**<constant int type static variable holds our goal width in mm.
                                                                                *first value for simulator , second value for ssl vision */
 
static const int OPP_GOAL_WIDTH               = OPP_GOAL_MAXY - OPP_GOAL_MINY;/**<constant int type static variable holds opponent goal widthin mm.
                                                                                *first value for simulator , second value for ssl vision */
																				
static const int CENTER_CIRCLE_DIAMETER       = SELECT(1000,50);/**<constant int type static variable holds diameter of centre circle in mm.
                                                                                *first value for simulator , second value for ssl vision */
																				
static const int DBOX_WIDTH                   = SELECT(500,20);       /**<constant int type static variable holds D box width along x direction in mm.
																	 *first value for simulator , second value for ssl vision */
																	 
static const int DBOX_HEIGHT                  = SELECT(600,40);       /**<Along Y direction(half height in each y direction) in mm.*/
static const int OPP_D                        = SELECT(2300,175);                                                                      

static const int DBOX_DEPTH                   = SELECTX(10, 10); /**<first value for simulator , second value for ssl vision.*/
static const int BALL_AT_CORNER_THRESH        = SELECT(20,10);    /**<Deciding pram for ball at corner of field.*/
/* Bot Parameteres configuration */
static const float ROTATION_FACTOR            = SELECT(0.05, 0.15);                

static const float RFACTOR                    = SELECT(3,   0.3);
static const float RFACTOR_SMALL              = SELECT(0.6, 0.15);

static const int CLEARANCE_PATH_PLANNER       = SELECT(500, 50);           /**< in mm.*/    
static const int MID_FIELD_THRESH             = SELECT(10, 10);            /**< in mm.*/ 
static const float BOT_RADIUS                 = SELECT(100, 13);           /**< in mm.*/ 
static const float SAFE_RADIUS 			          = (BOT_RADIUS * 5);      /**< in mm.*/ 
static const float COLLISION_DIST 			      = (BOT_RADIUS * 10);     /**< in mm.*/ 
static const int DRIBBLER_BALL_THRESH         = SELECT(400, 500);          /**< in mm.*/ 


static const int BOT_BALL_THRESH              = SELECT(100, 15);     /**< Minimum allowable threshhold distance between ball and bot in mm.*/
static const int BOT_POINT_THRESH             = SELECT(100, 10);     /**<Minimum allowable distance between bot and point.*/                 

static const int STRIP_WIDTH_X                = ForwardX(BOT_RADIUS*1.5);
static const int STRIP_WIDTH_Y                = BOT_RADIUS*1.5;
static const int MAX_FIELD_DIST               = SELECT(1000, 3500);              
static const float MAX_WHEEL_SPEED            = SELECT(2000, 450);              /**< in mm/s.*/             
static const float MAX_BOT_LINEAR_ACC         = SELECT(1000, 400);             /**< in mm/s/s.*/
static const float MAX_BOT_SPEED              = SELECT(2000, 350.0);           /**< in mm/s.*/
static const float MIN_BOT_SPEED              = SELECT(5, 1);                  /**< in mm/s.*/
static const float MAX_BOT_OMEGA              = SELECT(5, 3);                 /**< in rad/s//2.*/
static const float MIN_BOT_OMEGA              = SELECT(3, .5);                 /**< in rad/s.*/
static const float MAX_BACK_DRIBBLE_V_Y       = SELECT(500, 500);              /**< in mm/s.*/
static const float MAX_FRONT_DRIBBLE_V_Y      = SELECT(1200, 1200);            /**< in mm/s.*/
static const float MAX_DRIBBLE_V_X            = SELECT(200, 2000);              /**< in mm/s.*/
static const float MAX_DRIBBLE_R              = SELECT(3, 3);                   /**< in rad.*/
static const float DRIBBLER_BALL_ANGLE_RANGE  = SELECT(0.4f, 0.3f);             /**< in rad.*/
static const float SATISFIABLE_THETA          = SELECT(0.1f, 0.1f);             /**< in rad.*/
static const float SATISFIABLE_THETA_SHARP    = SELECT(0.01f, 0.01f);           /**< in rad.*/
static const float MAX_BALL_STEAL_DIST        = SELECT(800, 300);               /**< in mm.*/

static const float ZERO_VELOCITY_THRESHOLD    = SELECT(10, 10);  /**<If the velocity of a bot is below this value in mm/s, then the bot has effectively zero velocity.*/

static const int OUR_GOAL_Y = 500;/**<Parameters useful for camera's data transformation.*/
static const int OPP_GOAL_Y = 0;/**<Parameters useful for camera's data transformation.*/

static const float NETWORK_DELAY = SELECT(0.05, 0.05);  /**<Network Delay in miliseconds.*/

static const int HYSTERESIS = SELECT(20000,300); /**<Parameter for hysteresis adjutments.
                                                *Distance Hysteresis factor for switching of roles */
#endif //FIELD_CONFIG_H
