#ifndef WackBattle_AlwaysSameTest_h
#define WackBattle_AlwaysSameTest_h

#include <PriorityTest.h>

class AlwaysSameTest : PriorityTest {
public:
	AlwaysSameTest();
	void pushCategoryToPriority(int category);
	virtual const std::vector<int>& test(const Battle& battle) const;
private:
	std::vector<int> priority;
};

#endif
