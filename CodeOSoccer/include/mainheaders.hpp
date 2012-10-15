#ifndef MAINHEADERS
#define MAINHEADERS
#include "comdef.h"
#include "visionThread.h"
#include "logger.h"
#include "refBoxThread.h"
#include "rbCommDef.h"
#include "skillSet.h"
#include "kalman.h"
#include "fieldConfig.h"

// List all the tactics here to be included by main file.
#include "tactic.h"
#include "tGoalKeepingOppSide.hpp"
#include "tGoalKeepingOurSide.hpp"
#include "tPosition.hpp"
#include "tDefendPoint.hpp"
#include "tDefendLine.hpp"
#include "tDefendPoint.hpp"
#include "tDefend.hpp"
#include "tPositionForStart.hpp"
#include "tPositionForPenalty.hpp"
#include "tMarkBot.hpp"
#include "tStop.hpp"
#include "tVelocity.hpp"
#include "tBlock.hpp"
#include "tCommand.hpp"
#include "tSteal.hpp"
#include "tMarkBot.hpp"
#include "tCharge.hpp"
//#include "tDragToGoal.hpp"
#include "tKickToGoal.hpp"
#include "tShoot.hpp"
//#include "tDragToGoalOpp.hpp"
#include "tAttack.hpp"

int testcode(bool&);
int worker(bool&);

#endif
