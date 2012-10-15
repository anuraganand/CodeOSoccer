#include "bot_execute.h"
void run_bot(MyBot* bot, BeliefState *state) {
  TPositionP param0;
  param0.x = ForwardX(-1000);
  param0.y = 0;
  param0.align = false;
  param0.finalSlope = 0;
  param0.finalVelocity = 0;
  EXECUTE_BOT(bot, 0, Tactic::Position, param0);
  
  TPositionP param1;
  param1.x = ForwardX(0);
  param1.y = 1000;
  param1.align = false;
  param1.finalSlope = 0;
  param1.finalVelocity = 0;
  EXECUTE_BOT(bot, 1, Tactic::Position, param1);
  
  TPositionP param2;
  param2.x = ForwardX(1000);
  param2.y = 0;
  param2.align = 1.3;
  param2.finalSlope = 0;
  param2.finalVelocity = 0;
  EXECUTE_BOT(bot, 2, Tactic::Position, param2);
}
