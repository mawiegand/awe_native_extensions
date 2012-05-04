#include <Units.h>

#include <util/ErrorHandling.h>
#include <Battle.h>

Units::Units() : 
	numUnitsAtStart(0),
	numDeaths(0),
	numHits(0),
	numKills(0),
	newXp(0),
	unitTypeId(-1),
	unitCategoryId(-1)
{

}

bool Units::valid() const {
	return unitTypeId >= 0 && unitCategoryId >= 0;
}

void Units::foo() {
	awePtrCheck(0);
}

void Units::applyDamage(Battle& battle) {
	/*double enemyFactionStartSize = (double) battle.enemyFactionStartSize(myFaction);
	
	double superiorityProportion =  (((double) myFaction->startSize()) - enemyFactionStartSize)/enemyFactionStartSize;
	
	double superiorityBonus = 1 + superiorityProportion*superiorityFactor;
	
	if (superiorityBonus > superiorityBonusMax) {
		superiorityBonus = superiorityBonusMax;
	} else if (superiorityBonus < superiorityBonusMin) {
		superiorityBonus = superiorityBonusMin;
	}*/
}