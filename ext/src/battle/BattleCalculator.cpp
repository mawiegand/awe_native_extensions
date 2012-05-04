#include <BattleCalculator.h>

#include <set>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <util/Random.h>

#include <util/ErrorHandling.h>

#include <iostream>

BattleCalculator::BattleCalculator(double damageFactor) : damageFactor(damageFactor), superiorityFactor(0.33), superiorityBonusMin(1.0), superiorityBonusMax(2.0) {
	
}

bool BattleCalculator::callculateOneTick(Battle& battle) const {
	if (battle.factions.size() != 2) {
		aweError("the number of in the battle factions is != 2");
	}
	
	std::vector<Faction*>::iterator factionIt;
	for (factionIt = battle.factions.begin(); factionIt != battle.factions.end(); factionIt++) {
		//callculate the combined armies
		logMessage("callculate the combined armies");
		Army* ownArmy = (*factionIt)->combinedArmy();
		ownArmy->shuffle();
		ownArmy->sortByInitiative();
		Army* enemyArmy = battle.combinedEnemyArmy(*factionIt);
		enemyArmy->shuffle();
		
		//callculate the superiority bonus
		logMessage("callculate superiority bonus");
		double superiorityBonus = 1.0;
		{
			double enemyFactionStartSize = (double) enemyArmy->startSize();
			
			double superiorityProportion =  (((double) (*factionIt)->startSize()) - enemyFactionStartSize)/enemyFactionStartSize;
			
			superiorityBonus = 1 + superiorityProportion*superiorityFactor;
			
			if (superiorityBonus > superiorityBonusMax) {
				superiorityBonus = superiorityBonusMax;
			} else if (superiorityBonus < superiorityBonusMin) {
				superiorityBonus = superiorityBonusMin;
			}
		}
		
		//apply the damage
		logMessage("starting apply damage loop");
		bool damagePossible = true;
		while (damagePossible) {
			logMessage("apply damage loop");
			damagePossible = false;
			std::vector<Unit*>::iterator unitIt;
			for (unitIt = ownArmy->units.begin(); unitIt != ownArmy->units.end(); unitIt++) {
				awePtrCheck(*unitIt);
				//ignore units that can't hit anymore
				if ((*unitIt)->numUnitsAtStart - (*unitIt)->numHits <= 0) {
					continue;
				}
				//get attack priority
				int targetCategory = -1;
				{
					const std::vector<int>& attackPriority = battle.getUnitCategoryById((*unitIt)->unitCategoryId)->test->test((*factionIt), battle);
					//determine current target category
					{
						std::vector<int>::const_iterator targetIt;
						for (targetIt = attackPriority.begin(); targetIt != attackPriority.end(); targetIt++) {
							if (enemyArmy->getFirstAliveUnitOfCategory(*targetIt) != 0) {
								targetCategory = (*targetIt);
							}
						}
					}
				}
				
				//if there is a target damage it
				if (targetCategory != -1) {
					damagePossible = true;
					//lets apply the damage
					Army* targets = enemyArmy->getAllAliveUnitsOfCategory(targetCategory);
					(*unitIt)->applyDamage(superiorityBonus, targets);
				}
				
			}
		}
		
		delete enemyArmy;
		delete ownArmy;
	}
	return true;
}
