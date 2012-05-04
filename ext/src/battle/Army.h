#ifndef WackBattle_Army_h
#define WackBattle_Army_h

#include <cstddef>
#include <vector>
#include "Units.h"

class Army {
public:
	Army(int playerId);
	virtual ~Army();
	
	void addUnits(Units* units);
	Units* getUnits(size_t i);
	size_t numUnits() const; 
	
	int playerId;
	std::vector<Units*> units;
};

#endif
