#ifndef WackBattle_AlwaysSameTest_h
#define WackBattle_AlwaysSameTest_h

#include <PriorityTest.h>

#include <iostream>

class NoTest : public PriorityTest {
public:
	NoTest();
	virtual ~NoTest();
	void pushCategoryToPriority(int category);
	virtual const std::vector<int>& test(const Faction* myFaction, const Battle& battle, TestResult& result) const;
	
  virtual std::ostream& toString(std::ostream& out) const;
	
private:
	std::vector<int> priorities;
};




#endif
