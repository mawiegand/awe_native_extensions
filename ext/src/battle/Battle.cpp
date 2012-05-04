#include <Battle.h>

#include <util/ErrorHandling.h>

Battle::Battle() {

}
Battle::~Battle() {
	logMessage("DECONSTRUCTION Battle");
}

void Battle::addFaction(Faction* faction) {
	factions.push_back(faction);
}
Faction* Battle::getFaction(size_t i) {
	if (i >= factions.size()) {
		aweError("i was >= factions.size()");
	}
	return factions[i];
}
size_t Battle::numFactions() const {
	return factions.size();
}

void Battle::addUnitCategory(UnitCategory* category) {
	logMessage("addUnitCategory");
	logMessage(*category);
	categories.push_back(category);
}
UnitCategory* Battle::getUnitCategory(size_t i) {
	if (i >= categories.size()) {
		aweError("i was >= categories.size()");
	}
	return categories[i];
}
UnitCategory* Battle::getUnitCategoryById(int id) {
	std::vector<UnitCategory*>::iterator it;
	for (it = categories.begin(); it != categories.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->categoryId == id) {
			return (*it);
		}
	}
	aweError("could not find category for id");
	return 0;
}
size_t Battle::numUnitCategories() const {
	return categories.size();
}

bool Battle::isValid() const {
	return true;
}

size_t Battle::enemyFactionsStartSize(const Faction* myFaction) const {
	size_t re = 0;
	{
		std::vector<Faction*>::const_iterator it;
		for (it = factions.begin(); it != factions.end(); it++) {
			awePtrCheck(*it);
			if ((*it) != myFaction) {
				re += (*it)->startSize();
			}
		}
	}
	return re;
}

size_t Battle::enemyFactionsStartSizeOfCategory(int category, const Faction* myFaction) const {
	size_t re = 0;
	{
		std::vector<Faction*>::const_iterator it;
		for (it = factions.begin(); it != factions.end(); it++) {
			awePtrCheck(*it);
			if ((*it) != myFaction) {
				re += (*it)->startSizeOfCategory(category);
			}
		}
	}
	return re;
}

bool Battle::enemyFactionsHaveUnitsOfCategory(int category, const Faction* myFaction) const {
	std::vector<Faction*>::const_iterator it;
	for (it = factions.begin(); it != factions.end(); it++) {
		awePtrCheck(*it);
		if ((*it) != myFaction) {
			if ((*it)->hasOfUnitsCategory(category)) {
			
			}
		}
	}
	return true;
}

Army* Battle::combinedEnemyArmy(Faction* myFaction) {
	Army* re = new Army(-1);
	std::vector<Faction*>::const_iterator factionIt;
	for (factionIt = factions.begin(); factionIt != factions.end(); factionIt++) {
		awePtrCheck(*factionIt);
		if ((*factionIt) != myFaction) {
			std::vector<Army*>::const_iterator armyIt;
			for (armyIt = (*factionIt)->armies.begin(); armyIt != (*factionIt)->armies.end(); armyIt++) {
				awePtrCheck(*armyIt);
				std::vector<Unit*>::const_iterator unitIt;
				for (unitIt = (*armyIt)->units.begin(); unitIt != (*armyIt)->units.end(); unitIt++) {
					awePtrCheck(*unitIt);
					re->addUnit(*unitIt);
				}
			}
		}
	}
	return re;
}
