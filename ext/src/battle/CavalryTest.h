#ifndef WackBattle_CavalryTest_h
#define WackBattle_CavalryTest_h

#include <PriorityTest.h>

class CavalryTest {
public:
	CavalryTest();
	void pushCategoryToPriorityForFlankFail(int category);
	void pushCategoryToPriorityForFlankSuccess(int category);
	virtual const std::vector<int>& test(const Battle& battle) const;
private:
	std::vector<int> priorityForFlankFail;
	std::vector<int> priorityForFlankSuccess;
};


#endif
