#include <Army.h>

#include <util/ErrorHandling.h>
#include <util/Random.h>
#include <algorithm>

Army::Army(int playerId) : playerId(playerId) {

}

Army::~Army() {

}

void Army::addUnit(Unit* unit) {
	this->units.push_back(unit);
}

Unit* Army::getUnit(size_t i) {
	return units[i];
}
size_t Army::numUnits() const {
	return units.size();
}

size_t Army::startSize() const {
	size_t re = 0;
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		re += (*it)->numUnitsAtStart;
	}
	return re;
}

size_t Army::startSizeOfCategory(int category) const {
	size_t re = 0;
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->unitCategoryId == category) {
			re += (*it)->numUnitsAtStart;
		}
	}
	return re;
}

bool Army::hasOfUnitsCategory(int category) const {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->numUnitsAtStart > 0 && (*it)->unitCategoryId == category) {
			return true;
		}
	}
	return false;
}

void Army::shuffle() {
	util::Random::shuffle<Unit*>(units);
}

void Army::sortByInitiative() {
	std::sort(units.begin(), units.end(), Unit::initiativeGreater);
}