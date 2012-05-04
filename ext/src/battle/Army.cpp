#include <Army.h>

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
