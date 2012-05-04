#include <Battle.h>

#include <util/ErrorHandling.h>

Battle::Battle() {

}
Battle::~Battle() {

}

void Battle::addFaction(Faction* faction) {
	factions.push_back(faction);
}
Faction* Battle::getFaction(size_t i) {
	return factions[i];
}
size_t Battle::numFactions() const {
	return factions.size();
}

void Battle::addUnitCategory(UnitCategory* category) {
	categories.push_back(category);
}
UnitCategory* Battle::getUnitCategory(size_t i) {
	return categories[i];
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