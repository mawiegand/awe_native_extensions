#ifndef WackBattle_LineSizeTest_h
#define WackBattle_LineSizeTest_h

#include <PriorityTest.h>

class LineSizeTest {
public:
	LineSizeTest();
	void pushCategoryToPriorityOnFail(int category);
	void pushCategoryToPriorityOnSuccess(int category);
	virtual const std::vector<int>& test(const Battle& battle) const;
private:
	std::vector<int> prioritiesOnFail;
	std::vector<int> prioritiesOnSuccess;
};


#endif
