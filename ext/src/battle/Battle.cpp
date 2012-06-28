#include <Battle.h>

#include <util/ErrorHandling.h>
#include <set>

int Battle::numReferences = 0;

Battle::Battle() : factions(), categories(), seed(0) {
	numReferences++;
	//logMessage("CONSTRUCT Battle ref="<<numReferences);
}
Battle::~Battle() {
	numReferences--;
	//logMessage("DECONSTRUCTION Battle ref="<<numReferences);
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
	//logMessage("addUnitCategory");
	//logMessage(*category);
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
	//categories
	{
		std::vector<UnitCategory*>::const_iterator it;
		for (it = categories.begin(); it != categories.end(); it++) {
			if ((*it) == 0) return false;
			if (!(*it)->isValid()) return false;
		}
	}
	//factions
	{
		std::vector<Faction*>::const_iterator it;
		for (it = factions.begin(); it != factions.end(); it++) {
			if ((*it) == 0) return false;
			if (!(*it)->isValid()) return false;
		}
	}
	//check if all categories for all factions exist
	{
		//get categories
		std::set<int> categoryIds;
		std::vector<Faction*>::const_iterator fIt;
		for (fIt = factions.begin(); fIt != factions.end(); fIt++) {
			if ((*fIt) == 0) return false;
			std::vector<Army*>::const_iterator aIt;
			for (aIt = (*fIt)->armies.begin(); aIt != (*fIt)->armies.end(); aIt++) {
				if ((*aIt) == 0) return false;
				std::vector<Unit*>::const_iterator uIt;
				for (uIt = (*aIt)->units.begin(); uIt != (*aIt)->units.end(); uIt++) {
					if ((*uIt) == 0) return false;
					categoryIds.insert((*uIt)->unitCategoryId);
				}
			}
		}
		//check if categories exist
		std::set<int>::const_iterator cidIt;
		for (cidIt = categoryIds.begin(); cidIt != categoryIds.end(); cidIt++) {
			bool found = false;
			std::vector<UnitCategory*>::const_iterator cIt;
			for (cIt = categories.begin(); cIt != categories.end(); cIt++) {
				if ((*cIt) == 0) return false;
				if ((*cIt)->categoryId == (*cidIt)) {
					found = true;
					break;
				}
			}
			if (!found) return false;
		}
	}

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
