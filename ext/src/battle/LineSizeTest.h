#ifndef WackBattle_LineSizeTest_h
#define WackBattle_LineSizeTest_h

#include <PriorityTest.h>

class LineSizeTest : public PriorityTest {
public:
	LineSizeTest(int testCategoryId);
	virtual ~LineSizeTest();
	void pushCategoryToPriorityOnFail(int category);
	void pushCategoryToPriorityOnSuccess(int category);
	virtual const std::vector<int>& test(const Faction* myFaction, const Battle& battle) const;
	
  std::ostream& toString(std::ostream& out) const;

private:
	std::vector<int> prioritiesOnFail;
	std::vector<int> prioritiesOnSuccess;
	
	int testCategoryId;
	double minProportion;
	double minExponent;
	double minFactor;
	
	double normalFactor;
	double normalReduction;
	
	double maxPropotion;
	double maxProbability;
};


#endif
