#ifndef WackBattle_AlwaysSameTest_h
#define WackBattle_AlwaysSameTest_h

#include <PriorityTest.h>

class NoTest : PriorityTest {
public:
	NoTest();
	void pushCategoryToPriority(int category);
	virtual const std::vector<int>& test(const Battle& battle) const;
private:
	std::vector<int> priorities;
};

#endif
