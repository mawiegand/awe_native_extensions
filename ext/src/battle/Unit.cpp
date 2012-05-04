#include <Unit.h>

#include <util/ErrorHandling.h>
#include <Battle.h>
#include <Army.h>
#include <math.h>
#include <util/Random.h>

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
	unitCategoryId(-1),
	name(),
	damageTaken(0),
	damageInflicted(0),
	baseDamage(0),
	criticalDamage(0),
	criticalProbability(0),
	initiative(0),
	hitpoints(0),
	armor(0),
	xpFactorPerUnit(0)
{

}

Unit::~Unit() {
	logMessage("DECONSTRUCTION Unit");
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
		
		double deaths = numDeadUnits(numHittingUnits, superiorityBonus, *targetIt);
		//overkill
		/*logMessage("numHittingUnits:");
		logMessage(numHittingUnits);*/
		/*logMessage("DEATHS:");
		logMessage(deaths);*/
		if (deaths + ((double)(*targetIt)->numDeaths) > (*targetIt)->numUnitsAtStart) {
			damageInflicted += ((*targetIt)->numUnitsAtStart-(*targetIt)->numDeaths)*(*targetIt)->hitpoints;
			numKills += ((*targetIt)->numUnitsAtStart-(*targetIt)->numDeaths);
			(*targetIt)->numDeaths = (*targetIt)->numUnitsAtStart;
			(*targetIt)->damageTaken = (*targetIt)->numUnitsAtStart * (*targetIt)->hitpoints;
			(*targetIt)->newXp = ((double)(*targetIt)->numUnitsAtStart) * (*targetIt)->xpFactorPerUnit;
			//callculate the hits that are left
			//1 - living/Tote = Überschlag
			double overkill = 1.0-(((*targetIt)->numUnitsAtStart-(*targetIt)->numDeaths)/deaths);
			numHits +=  (numHittingUnits-(overkill*numHittingUnits));
		//all damage has been dealt
		} else {
			damageInflicted += deaths * (*targetIt)->hitpoints;
			double p = deaths-floor(deaths);
			if (p > 0.0) {
				if (util::Random::random(p)) {
					deaths = ceil(deaths);
				} else {
					deaths = floor(deaths);
				}
			}
			numKills += (size_t)deaths;
			numHits += numHittingUnits;
			(*targetIt)->numDeaths += deaths;
			(*targetIt)->damageTaken += deaths * (*targetIt)->hitpoints;
			(*targetIt)->newXp += deaths * (*targetIt)->xpFactorPerUnit;
		}
		
	}
	
}