#ifndef WackBattle_UnitCategory_h
#define WackBattle_UnitCategory_h

#include <PriorityTest.h>

class UnitCategory {
public:
	UnitCategory();
	virtual ~UnitCategory() {}
	virtual int getID() = 0;
	virtual void getTargetClass() = 0;

	PriorityTest* test;
};

#endif
