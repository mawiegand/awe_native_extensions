#include <Faction.h>


Faction::Faction() {}
Faction::~Faction() {}

void Faction::addArmy(Army* army) {
	armies.push_back(army);
}
size_t Faction::numArmies() const {
	return armies.size();
}
Army* Faction::getArmy(size_t i) {
	return armies[i];
}