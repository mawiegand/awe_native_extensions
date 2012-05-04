#include <BattleCalculator.h>

#include <set>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <util/Random.h>

#include <iostream>

BattleCalculator::BattleCalculator(double damageFactor) : damageFactor(damageFactor), m_categories() {
	
}

bool BattleCalculator::callculateOneTick(Battle& battle) const {
	return callculateOneTick(battle.factions);
}

bool BattleCalculator::callculateOneTick(std::vector<Faction*>& factions) const {
	
	return false;
}

double BattleCalculator::random() {
	return (double(rand()) / double(RAND_MAX));
}
bool BattleCalculator::random(double probability) {
	assert(probability >= 0.0 && probability <= 1.0);
	return (BattleCalculator::random()) < probability;
}
double BattleCalculator::random01(double probability) {
	return BattleCalculator::random(probability)?1.0:0.0;
}
size_t BattleCalculator::random(size_t start, size_t end) {
	assert(start <= end);
	return start + size_t(round(BattleCalculator::random()*(double(end-start))));
}
