#ifndef WackBattle_PriorityTest_h
#define WackBattle_PriorityTest_h

#include <vector>

class Battle;

class PriorityTest {
public:
	virtual ~PriorityTest() {}
	virtual const std::vector<int>& test(const Battle& battle) const = 0;
};

#endif
