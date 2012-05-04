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
		aweError("the number of in the battle factions is != 2");
	}
	std::vector<Faction*>::iterator factionIt;
	for (factionIt = battle.factions.begin(); factionIt != battle.factions.end(); factionIt++) {
		Army* ownArmy = (*factionIt)->combinedArmy();
		ownArmy->shuffle();
		ownArmy->sortByInitiative();
		Army* enemyArmy = battle.combinedEnemyArmy(*factionIt);
		enemyArmy->shuffle();
		
		std::vector<Unit*>::iterator unitIt;
		for (unitIt = ownArmy->units.begin(); unitIt != ownArmy->units.end(); unitIt++) {
			awePtrCheck(*unitIt);
			//get attack priority
			const std::vector<int>& attackPriority = battle.getUnitCategoryById((*unitIt)->unitCategoryId)->test->test((*factionIt), battle);
			//get the current target
			
		}
		
		delete enemyArmy;
		delete ownArmy;
	}
	return true;
}
