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
	
	std::vector<Army*> armies;
};

#endif
