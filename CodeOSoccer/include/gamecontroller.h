#ifndef GAME_CONROLLER
#define GAME_CONROLLER
///Enum for team colour blue or yellow
enum Team
{
  BLUE,
  YELLOW
};
/**Changes home and away bot colours and IDs
 * @param usePositiveXSide : whether my team is towards positive x or negetive x. 
 * @param myteam : colour of my team(BLUE/YELLOW).
 */
int startgame(bool usePositiveXSide, Team myteam);
#endif