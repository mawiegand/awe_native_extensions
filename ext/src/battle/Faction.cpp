#include <Faction.h>

#include <util/ErrorHandling.h>

Faction::Faction() {}
Faction::~Faction() {
	logMessage("DECONSTRUCTION Faction");
}

bool Faction::isValid() const {
	std::vector<Army*>::const_iterator it;
	for (it = armies.begin(); it != armies.end(); it++) {
		if ((*it) == 0) return false;
		if (!(*it)->isValid()) return false;
	}
	return true;
}

void Faction::addArmy(Army* army) {
	armies.push_back(army);
}
size_t Faction::numArmies() const {
	return armies.size();
}
Army* Faction::getArmy(size_t i) {
	if (i >= numArmies()) {
		aweError("i was >= armies.size()");
	}
	return armies[i];
}

size_t Faction::startSize() const {
	size_t num = 0;
	std::vector<Army*>::const_iterator it;
	for (it = armies.begin(); it != armies.end(); it++) {
		awePtrCheck(*it);
		num += (*it)->startSize();
	}
	return num;
}

size_t Faction::startSizeOfCategory(int category) const {
	size_t num = 0;
	std::vector<Army*>::const_iterator it;
	for (it = armies.begin(); it != armies.end(); it++) {
		awePtrCheck(*it);
		num += (*it)->startSizeOfCategory(category);
	}
	return num;
}

bool Faction::hasOfUnitsCategory(int category) const {
	std::vector<Army*>::const_iterator it;
	for (it = armies.begin(); it != armies.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->hasUnitsOfCategory(category)) {
			return true;
		}
	}
	return false;
}

TestResult* Faction::getTestResult(size_t elem) {
	if (elem >= testResults.size()) {
		aweError("getTestResult(i) i is bigger then the mass of test results");
	}
	std::map<int, TestResult*>::iterator it = testResults.begin();
	for (size_t i = 0; i < elem; i++) {
		it++;
	}
	return it->second;
}
size_t Faction::testResultsSize() const {
	return testResults.size();
}

Army* Faction::combinedArmy() {
	Army* re = new Army(-1);
	std::vector<Army*>::const_iterator armyIt;
	for (armyIt = armies.begin(); armyIt != armies.end(); armyIt++) {
		awePtrCheck(*armyIt);
		std::vector<Unit*>::const_iterator unitIt;
		for (unitIt = (*armyIt)->units.begin(); unitIt != (*armyIt)->units.end(); unitIt++) {
			re->addUnit(*unitIt);
		}
	}
	return re;
}