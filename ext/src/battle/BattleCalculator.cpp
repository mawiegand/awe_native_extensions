#include <BattleCalculator.h>

#include <set>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <util/Random.h>

#include <util/ErrorHandling.h>

#include <iostream>

BattleCalculator::BattleCalculator(double damageFactor) : damageFactor(damageFactor){
	
}

bool BattleCalculator::callculateOneTick(Battle& battle) const {
	if (battle.factions.size() != 2) {
		aweError("");
	}

	return true;
}
