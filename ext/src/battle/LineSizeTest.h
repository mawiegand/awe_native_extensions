#ifndef WackBattle_LineSizeTest_h
#define WackBattle_LineSizeTest_h

#include <PriorityTest.h>

class LineSizeTest : public PriorityTest {
public:
	LineSizeTest(int testCategoryId);
	void pushCategoryToPriorityOnFail(int category);
	void pushCategoryToPriorityOnSuccess(int category);
	virtual const std::vector<int>& test(const Faction* myFaction, const Battle& battle) const;
private:
	std::vector<int> prioritiesOnFail;
	std::vector<int> prioritiesOnSuccess;
	
	int testCategoryId;
};


#endif
