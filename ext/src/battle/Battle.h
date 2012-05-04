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
	UnitCategory* getUnitCategoryById(int id);
	
	bool isValid() const;
	
	size_t enemyFactionsStartSize(const Faction* myFaction) const;
	size_t enemyFactionsStartSizeOfCategory(int category, const Faction* myFaction) const;
	bool enemyFactionsHaveUnitsOfCategory(int category, const Faction* myFaction) const;
	
	Army* combinedEnemyArmy(Faction* myFaction);

	std::vector<Faction*> factions;
	std::vector<UnitCategory*> categories;
};

#endif
