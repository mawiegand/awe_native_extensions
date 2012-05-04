#ifndef WackBattle_UnitCategory_h
#define WackBattle_UnitCategory_h

#include <PriorityTest.h>
#include <string>

class UnitCategory {
public:
	UnitCategory(int categoryId, const std::string& name);
	virtual ~UnitCategory();

	int categoryId;
	std::string name;

	PriorityTest* test;
};

#endif
