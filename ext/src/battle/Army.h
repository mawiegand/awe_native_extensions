#ifndef WackBattle_Army_h
#define WackBattle_Army_h

#include <cstddef>
#include <vector>
#include <Unit.h>

class Army {
public:
	static int numReferences;
public:
	Army(int playerId);
	virtual ~Army();
	
	bool isValid() const;
	
	void addUnit(Unit* unit);
	Unit* getUnit(size_t i);
	size_t numUnits() const;
	
	size_t startSize() const;
	size_t startSizeOfCategory(int category) const;
	
	size_t numUnitsAlive() const;
	
	bool hasUnitsOfCategory(int category) const;
	bool hasLivingUnitsOfCategory(int category) const;
	Unit* getFirstAliveUnitOfCategory(int category);
	void getAllUnitsOfCategory(int category, std::vector<Unit*>& result);
	void getAllLivingUnitsOfCategory(int category, std::vector<Unit*>& result);
	Army* getAllLivingUnitsOfCategory(int category);
	
	int numKills() const;
	
	void shuffle();
	void sortByInitiative();
	
	int playerId;
	std::vector<Unit*> units;
};

template<class OStream>
OStream& operator<<(OStream& out, const Army& army) {
	out<<"Army( \n";
	out<<"\t"<<"playerId="<<army.playerId<<"\n";
	out<<"\t"<<"units="<<"\n";
	std::vector<Unit*>::const_iterator it;
	for (it = army.units.begin(); it != army.units.end(); it++) {
		out<<(*(*it))<<"\n";
	}
	out<<")\n";
    return out;
}

#endif
