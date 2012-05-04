#include <Battle.h>

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

void Battle::checkValidity() const {
	
}