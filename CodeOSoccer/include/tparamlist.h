#ifndef TPARAM_LIST
#define TPARAM_LIST
typedef struct TDefaultP
{
  int defaultp;
} TDefaultP;

///@struct TBlockP Parameters for the tactic TBlock.
typedef struct TBlockP
{
  float dist;  ///<Distance from the ball .
  int side;	   ///<Side (-1 for left, 1 for right).
} TBlockP;

/**@struct TDefendLineP Parameters for the tactic TDefendLine.
	   * @see TDefendLine*/
typedef struct TDefendLineP
{
  int x1, x2, y1, y2; ///<line joining x1,y1 andx2,y2 . 
  int radius; /**< radius of circle around point in which bot will defend.*/
} TDefendLineP;

/**@struct TPositionP Parameters for the tactic TPosition, TPositionForPenalty, TPositionForStart. */
typedef struct TPositionP
{
  float x ;          ///< Point x coordinate .
  float y ;			 ///< Point y coordinate .
  float finalSlope ; ///< Point finalSlope .
  float finalVelocity ; ///< Point finalVelocity .
  bool align;           ///< align (True or False) .
} TPositionP;

typedef struct TCommandP
{

    float v_x;  ///Velocity x component.
	float v_y;  ///<Velocity y component.
	float v_t;  ///< Angular Velocity component.
	float power;  ///<Power with to hit the ball.
	bool dribble; ///<whether dribbler is running or not.
} TCommandP;

typedef struct TPositionP TPositionForStartP;

typedef struct TPositionP TPositionForPenaltyP;

/**@struct TVelocityP Parameters for the tactic TVelocity.
	   * @see TVelocity*/
typedef struct TVelocityP
{
  float v_x;  ///<Velocity x component.
  float v_y;  ///<Velocity y component.
  float v_t;  ///< Angular Velocity component.
} TVelocityP;

/**@struct TKickP Parameters for the tactic TKick.
	   * @see TKick*/
typedef struct TKickP
{
  float power;  ///<Power with to hit the ball.
} TKickP;

typedef struct TKickToGoalP
{
  float power;  /**<Power with to hit the ball.*/
} TKickToGoalP;
/**@struct TDefendPointP Parameters for the tactic TDefendPoint.
	   * @see TDefendPoint*/
typedef struct TDefendPointP
{
  int x, y;   ///< x,y coordinate of defendpoint.
  int radius ; ///< radius of circle around point in which bot will defend.
} TDefendPointP;

/**@struct TDefendP Parameters for the tactic TDefend.
	   * @see TDefend*/
typedef struct TDefendP
{
  int x;    ///< x coordinate for defend.
} TDefendP;

/**@struct TMarkBotP Parameters for the tactic TMarkBot.
	   * @see TMarkBot*/
typedef struct TMarkBotP
{
  int awayBotID ;    ///< BotID of the opponent's Bot
} TMarkBotP;
#endif