#include <Army.h>

#include <util/ErrorHandling.h>
#include <util/Random.h>
#include <algorithm>

int Army::numReferences = 0;

Army::Army(int playerId) : playerId(playerId) {
	numReferences++;
}

Army::~Army() {
	numReferences--;
	logMessage("DECONSTRUCTION Army");
}

bool Army::isValid() const {
	std::vector<Unit*>::const_iterator it;
	for (it = units.begin(); it != units.end(); it++) {
		if ((*it) == 0) return false;
		if (!(*it)->isValid()) return false;
	}
	return true;
}

void Army::addUnit(Unit* unit) {
	this->units.push_back(unit);
}

Unit* Army::getUnit(size_t i) {
	if (i >= numUnits()) {
		aweError("i was >= units.size()");
	}
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

size_t Army::numUnitsAlive() const {
	size_t re = 0;
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		re += (*it)->numUnitsAtStart - (*it)->numDeaths;
	}
	return re;
}

bool Army::hasUnitsOfCategory(int category) const {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->numUnitsAtStart > 0 && (*it)->unitCategoryId == category) {
			return true;
		}
	}
	return false;
}

bool Army::hasLivingUnitsOfCategory(int category) const {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->numUnitsAtStart > 0 && (*it)->unitCategoryId == category && (*it)->numUnitsAtStart > (*it)->numDeaths) {
			return true;
		}
	}
	return false;
}

Unit* Army::getFirstAliveUnitOfCategory(int category) {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if (!(*it)->isValid()) {
			aweError("Unit was not valid");
		}
		if ((*it)->numUnitsAtStart > 0 && (*it)->unitCategoryId == category && (*it)->numUnitsAtStart > (*it)->numDeaths) {
			return (*it);
		}
	}
	return 0;
}

void Army::getAllUnitsOfCategory(int category, std::vector<Unit*>& result) {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->unitCategoryId == category) {
			result.push_back(*it);
		}
	}
}

void Army::getAllLivingUnitsOfCategory(int category, std::vector<Unit*>& result) {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->unitCategoryId == category && (*it)->numUnitsAtStart > (*it)->numDeaths) {
			//logMessage("alive added");
			//logMessage(**it);
			result.push_back(*it);
		}
	}
}

Army* Army::getAllLivingUnitsOfCategory(int category) {
	Army* re = new Army(-1);
	//logMessage("created dummy army");
	getAllLivingUnitsOfCategory(category, re->units);
	//logMessage("filled dummy army");
	//logMessage(*re);
	//logMessage("dummy army done");
	return re;
}

int Army::numKills() const {
	int num = 0;
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		num += (*it)->numKills;
	}
	return num;
}

void Army::shuffle() { logMessage("IN ARMY::SHUFFLE");
	util::Random::shuffle<Unit*>(units);
}

void Army::sortByInitiative() {
	std::sort(units.begin(), units.end(), Unit::initiativeGreater);
}
