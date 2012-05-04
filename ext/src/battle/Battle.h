#ifndef WackBattle_Battle_h
#define WackBattle_Battle_h

#include <vector>
#include <Faction.h>
#include <UnitCategory.h>

class Battle {
public:
	Battle();
	virtual ~Battle();

	void addFaction(Faction* faction);
	Faction* getFaction(size_t i);
	size_t numFactions() const;
	
	void addUnitCategory(UnitCategory* category);
	UnitCategory* getUnitCategory(size_t i);
	size_t numUnitCategories() const;
	
	void checkValidity() const;
	
	size_t enemyFactionsStartSize(const Faction* myFaction) const;
	size_t enemyFactionsStartSizeOfCategory(int category, const Faction* myFaction) const;
	bool enemyFactionsHaveUnitsOfCategory(int category, const Faction* myFaction) const;

	std::vector<Faction*> factions;
	std::vector<UnitCategory*> categories;
};

#endif
