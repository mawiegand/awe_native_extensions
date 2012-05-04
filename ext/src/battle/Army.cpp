#include <Army.h>

#include <util/ErrorHandling.h>

Army::Army(int playerId) : playerId(playerId) {

}

Army::~Army() {

}

void Army::addUnits(Units* units) {
	this->units.push_back(units);
}

Units* Army::getUnits(size_t i) {
	return units[i];
}
size_t Army::numUnits() const {
	return units.size();
}

size_t Army::startSize() const {
	size_t re = 0;
	std::vector<Units*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		re += (*it)->numUnitsAtStart;
	}
	return re;
}

size_t Army::startSizeOfCategory(int category) const {
	size_t re = 0;
	std::vector<Units*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->unitCategoryId == category) {
			re += (*it)->numUnitsAtStart;
		}
	}
	return re;
}

bool Army::hasOfUnitsCategory(int category) const {
	std::vector<Units*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->numUnitsAtStart > 0 && (*it)->unitCategoryId == category) {
			return true;
		}
	}
	return false;
}