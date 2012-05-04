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

template<class OStream>
OStream& operator<<(OStream& out, const Battle& battle) {
	out<<"Battle( \n";
	out<<"\t"<<"categories="<<"\n";
	{
		std::vector<UnitCategory*>::const_iterator it;
		for (it = battle.categories.begin(); it != battle.categories.end(); it++) {
			out<<(*(*it))<<"\n";
		}
	}
	out<<"\t"<<"factions="<<"\n";
	{
		std::vector<Faction*>::const_iterator it;
		for (it = battle.factions.begin(); it != battle.factions.end(); it++) {
			out<<(*(*it))<<"\n";
		}
	}
	out<<")\n";
    return out;
}

#endif
