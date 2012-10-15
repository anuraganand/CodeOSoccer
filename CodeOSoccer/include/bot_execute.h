#ifndef BOT_EXECUTE_H
#define BOT_EXECUTE_H
#include <tparamlist.h>
#include <tactic.h>
#include <my_bot.h>
#include <beliefState.h>
using namespace Strategy;
 /** converts tatic param to pamam for the union */
inline Strategy::Tactic::Param makeTacticParam(void* param) { 
  Strategy::Tactic::Param _param;
  memcpy(&_param, param, sizeof _param);
  return _param;
}

#define EXECUTE_BOT(bot, botid, TacticID, TacticParam) bot->executeTactic(botid, TacticID, makeTacticParam(&TacticParam)) /** run the tatic  *@param TacticID for the bot with bot ID *@param botid. Takes parameter *@param TacticParam for the tatic*/

void run_bot(Strategy::MyBot* bot, Strategy::BeliefState *state);
#endif