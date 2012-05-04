#ifndef WakBattle_BattleCalculator_h
#define WakBattle_BattleCalculator_h

#include <Faction.h>
#include <Army.h>
#include <map>
#include <Battle.h>
#include <UnitCategory.h>
#include <vector>

///Class to callculate a Battle.
class BattleCalculator {
public:
	///Creates a BattleCalculator.
	///@param damageFactor all the damageValues during a Battle will be multiplied by this factor
	BattleCalculator(double damageFactor = 1.0);
	
	///Callculate one tick of a Battle
	///@param Battle the Battle
	///@return returns true if the Battle is over
	bool callculateOneTick(Battle& Battle) const;
	
	///All the damageValues during a Battle will be multiplied by this factor.
	///This helps to control the number of ticks needed until a Battle is over (bigger = faster, smaller = slower).
	double damageFactor;
	double superiorityFactor;
	double superiorityBonusMin;
	double superiorityBonusMax;
};

#endif
