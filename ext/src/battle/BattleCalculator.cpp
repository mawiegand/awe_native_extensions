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

BattleCalculator::~BattleCalculator() {
	logMessage("DECONSTRUCTION LineSizeTest");
}

bool BattleCalculator::callculateOneTick(Battle& battle) const {
  logMessage("IN BATTLE CALC");

	logMessage(battle);

	if (battle.factions.size() != 2) {
		aweError("the number of in the battle factions is != 2");
	}

	logMessage("START BATTLE");
	
	std::vector<Faction*>::iterator factionIt;
	for (factionIt = battle.factions.begin(); factionIt != battle.factions.end(); factionIt++) {

		//callculate the combined armies
		//logMessage("callculate the combined armies");
		Army* ownArmy = (*factionIt)->combinedArmy();
		ownArmy->shuffle();
		ownArmy->sortByInitiative();
		Army* enemyArmy = battle.combinedEnemyArmy(*factionIt);
		enemyArmy->shuffle();
		
		//callculate the superiority bonus
		//logMessage("callculate superiority bonus");
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
		
		logMessage("APPLY DAMAGE");

		//apply the damage
		//logMessage("starting apply damage loop");
		bool damagePossible = true;
		int round = 1;
		while (damagePossible) {
			logMessage("Round:");
			logMessage(round);
			round++;
			//logMessage("apply damage loop");
			damagePossible = false;
			std::vector<Unit*>::iterator unitIt;
			for (unitIt = ownArmy->units.begin(); unitIt != ownArmy->units.end(); unitIt++) {
				awePtrCheck(*unitIt);
				//ignore units that can't hit anymore
				if (((double)(*unitIt)->numUnitsAtStart) - (*unitIt)->numHits <= 0.5) {
					continue;
				}
				//get attack priority
				int targetCategory = -1;
				{
					//logMessage("get attack priority");
					const std::vector<int>& attackPriority = battle.getUnitCategoryById((*unitIt)->unitCategoryId)->test->test((*factionIt), battle);
					//determine current target category
					{
						//logMessage("determine current target category");
						std::vector<int>::const_iterator targetIt;
						for (targetIt = attackPriority.begin(); targetIt != attackPriority.end(); targetIt++) {
							if (enemyArmy->hasLivingUnitsOfCategory(*targetIt)) {
								targetCategory = (*targetIt);
                break; // leave loop, because found a category that can be hit.
							}
						}
            logMessage("Unit of category " << (*unitIt)->unitCategoryId << " strikes enemy of category " << targetCategory << "." << std::endl);
					}
				}
				
				//if there is a target damage it
				if (targetCategory != -1) {
					//logMessage("appling damage");
					//logMessage(targetCategory);
					damagePossible = true;
					//lets apply the damage
					Army* targets = enemyArmy->getAllLivingUnitsOfCategory(targetCategory);
					//logMessage(*targets);
					(*unitIt)->applyDamage(superiorityBonus, targets);
					delete targets;
				}
				
			}
		}
		
		delete enemyArmy;
		delete ownArmy;
	}
	return true;
}
