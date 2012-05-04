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

