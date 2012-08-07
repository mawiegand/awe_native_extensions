#include <BattleCalculator.h>

#include <set>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <util/Random.h>

#include <util/ErrorHandling.h>
#include <util/MemoryManagement.h>

#include <iostream>

BattleCalculator::BattleCalculator(double damageFactor) : damageFactor(damageFactor), superiorityFactor(0.05), superiorityBonusMin(-0.25), superiorityBonusMax(0.5) {
	
}

BattleCalculator::~BattleCalculator() {
	//logMessage("DECONSTRUCTION BattleCalculator");
}


bool BattleCalculator::callculateOneTick(Battle& battle) const {
	
	logMessage("started BattleCalculator::callculateOneTick");
	logMessage("set seed to"<<battle.seed);
	util::Random::setSeed(battle.seed);
	
	//logMessage(battle);

	if (battle.factions.size() != 2) {
		aweError("the number of in the battle factions is != 2");
	}
	
	std::vector<Faction*>::iterator factionIt;
	for (factionIt = battle.factions.begin(); factionIt != battle.factions.end(); factionIt++) {

		logMessage("\t"<<"callculating damage for faction");

		//callculate the combined armies
		//logMessage("callculate the combined armies");
		Army* ownArmy = (*factionIt)->combinedArmy();
		ownArmy->shuffle();
		ownArmy->sortByInitiative();
		Army* enemyArmy = battle.combinedEnemyArmy(*factionIt);
		enemyArmy->shuffle();
		
		//callculate the attack priorities for the unit types
		std::map<int, std::vector<int> const*> priorityCache;
		
		//callculate the superiority bonus
		//logMessage("callculate superiority bonus");
		double superiorityBonus = 0.0;
		{
			double enemyFactionStartSize = (double) enemyArmy->startSize();
			
			double superiorityProportion =  (((double) (*factionIt)->startSize()) - enemyFactionStartSize)/enemyFactionStartSize;
			
			superiorityBonus = superiorityProportion*superiorityFactor;
			
			if (superiorityBonus > superiorityBonusMax) {
				superiorityBonus = superiorityBonusMax;
			} else if (superiorityBonus < superiorityBonusMin) {
				superiorityBonus = superiorityBonusMin;
			}
		}
		
		//logMessage("APPLY DAMAGE");

		//apply the damage
		//logMessage("starting apply damage loop");
		bool damagePossible = true;
		int round = 1;
		while (damagePossible) {
			//logMessage("\t\tdamage round");
			round++;
			//logMessage("apply damage loop");
			damagePossible = false;
			std::vector<Unit*>::iterator unitIt;
			for (unitIt = ownArmy->units.begin(); unitIt != ownArmy->units.end(); unitIt++) {
				//logMessage("\t\t\tunit round typeId="<<(*unitIt)->unitTypeId);
				awePtrCheck(*unitIt);
				//ignore units that can't hit anymore
				if (((double)(*unitIt)->numUnitsAtStart) - (*unitIt)->numHits <= 0.5) {
					//logMessage("\t\t\t\tignoring, units-hits <= 0.5");
					continue;
				}
				//get attack priority
				int targetCategory = -1;
				{
					//logMessage("get attack priority");
					std::vector<int> const* attackPriorityPtr = 0;
					std::map<int, std::vector<int> const*>::const_iterator cacheResult = priorityCache.find((*unitIt)->unitCategoryId) ;
					if (cacheResult == priorityCache.end()) {
						TestResult* testResult = new TestResult();
						(*factionIt)->testResults[(*unitIt)->unitCategoryId] = testResult;
						awe::MemoryManagement::registerNewObject(testResult);
						//aweRegisterNewObject(testResult, TestResult);
						#ifdef SWIG
							//SWIG_NewPointerObj((void*)testResult, SWIGTYPE_p_TestResult, SWIG_POINTER_OWN);
						#endif

						attackPriorityPtr = &(battle.getUnitCategoryById((*unitIt)->unitCategoryId)->test->test(
							(*factionIt), 
							battle, 
							(*testResult)
						));
						priorityCache[(*unitIt)->unitCategoryId] = attackPriorityPtr;
					} else {
						//logMessage("loaded cached test data");
						attackPriorityPtr = cacheResult->second;
					}
					//const std::vector<int>& attackPriority = 
					//determine current target category
					{
						//logMessage("determine current target category");
						std::vector<int>::const_iterator targetIt;
						for (targetIt = attackPriorityPtr->begin(); targetIt != attackPriorityPtr->end(); targetIt++) {
							if (enemyArmy->hasLivingUnitsOfCategory(*targetIt)) {
								targetCategory = (*targetIt);
								break; // leave loop, because found a category that can be hit.
							}
						}
						//logMessage("Unit of category " << (*unitIt)->unitCategoryId << " strikes enemy of category " << targetCategory << "." << std::endl);
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
	logMessage("finished BattleCalculator::callculateOneTick");
	return true;
}
