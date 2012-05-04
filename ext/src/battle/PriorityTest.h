#ifndef WackBattle_PriorityTest_h
#define WackBattle_PriorityTest_h

#include <vector>

class Battle;
class Faction;

class PriorityTest {
public:
	virtual ~PriorityTest() {}
	virtual const std::vector<int>& test(const Faction* myFaction, const Battle& battle) const = 0;
};

#endif
