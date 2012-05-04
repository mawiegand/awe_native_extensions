#ifndef WackBattle_Army_h
#define WackBattle_Army_h

#include <cstddef>
#include <vector>
#include <Unit.h>

class Army {
public:
	Army(int playerId);
	virtual ~Army();
	
	void addUnit(Unit* unit);
	Unit* getUnit(size_t i);
	size_t numUnits() const;
	
	size_t startSize() const;
	size_t startSizeOfCategory(int category) const;
	
	size_t numUnitsAlive() const;
	
	bool hasOfUnitsCategory(int category) const;
	Unit* getFirstAliveUnitOfCategory(int category);
	void getAllUnitsOfCategory(int category, std::vector<Unit*> result);
	void getAllAliveUnitsOfCategory(int category, std::vector<Unit*> result);
	Army* getAllAliveUnitsOfCategory(int category);
	
	int numKills() const;
	
	void shuffle();
	void sortByInitiative();
	
	int playerId;
	std::vector<Unit*> units;
};

#endif
