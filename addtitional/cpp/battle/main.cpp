#include <iostream>
#include <BattleCalculator.h>

int main (int argc, const char * argv[])
{
	using namespace std;
	
	Faction* factionA = new Faction();
	Faction* factionB = new Faction();
	
	UnitCategory* category0 = new UnitCategory(0);
	UnitCategory* category1 = new UnitCategory(1);
	UnitCategory* category2 = new UnitCategory(2);
	
	Army* armyA1 = new Army(1);
	factionA->addArmy(armyA1);
	Unit* unitA11 = new Unit();
	unitA11->unitCategoryId = 0;
	armyA1->addUnit(unitA11);
	
	Army* armyB1 = new Army(1);
	factionB->addArmy(armyB1);
	Unit* unitB11 = new Unit();
	unitB11->unitCategoryId = 0;
	armyB1->addUnit(unitB11);
	
	Battle* battle = new Battle();
	battle->addFaction(factionA);
	battle->addFaction(factionB);
	battle->addUnitCategory(category0);
	battle->addUnitCategory(category1);
	battle->addUnitCategory(category2);
	
	BattleCalculator bc;
	bc.callculateOneTick(*battle);
	
    return 0;
}

