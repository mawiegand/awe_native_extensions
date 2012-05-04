#include <Unit.h>

#include <util/ErrorHandling.h>
#include <Battle.h>
#include <Army.h>

bool Unit::initiativeGreater(const Unit* a, const Unit* b) {
	awePtrCheck(a);
	awePtrCheck(b);
	return (a->initiative > b->initiative);
}

Unit::Unit() : 
	numUnitsAtStart(0),
	numDeaths(0),
	numHits(0),
	numKills(0),
	newXp(0),
	unitTypeId(-1),
	unitCategoryId(-1)
{

}

bool Unit::valid() const {
	return unitTypeId >= 0 && unitCategoryId >= 0 && numUnitsAtStart >= numDeaths;
}

double Unit::numDeadUnits(double numHitting, double superiorityBonus, Unit* target) const {
	return (criticalDamage*criticalProbability)/target->hitpoints + baseDamage/(target->hitpoints + target->armor) * numHitting * superiorityBonus;
}

void Unit::applyDamage(double superiorityBonus, Army* targets) {
	double numTargetsAlive = ((double) targets->numUnitsAlive());
	double pFactor = (((double) numUnitsAtStart) - ((double) numHits))/numTargetsAlive; 
	std::vector<Unit*>::iterator targetIt;
	for (targetIt = targets->units.begin(); targetIt != targets->units.end(); targetIt++) {
		double numHittingUnits = (((double) (*targetIt)->numUnitsAtStart) - ((double) (*targetIt)->numDeaths)) *pFactor;
		
		//double deaths = 
		
	}
	
}