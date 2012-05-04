#ifndef WackBattle_Faction_h
#define WackBattle_Faction_h

#include <Army.h>

class Faction {
public:
	Faction();
	virtual ~Faction();
	
	void addArmy(Army* army);
	size_t numArmies() const;
	Army* getArmy(size_t i);
	
	size_t startSize() const;
	size_t startSizeOfCategory(int category) const;
	bool hasOfUnitsCategory(int category) const;
	
	std::vector<Army*> armies;
};

#endif
