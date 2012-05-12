#ifndef WackBattle_UnitCategory_h
#define WackBattle_UnitCategory_h

#include <PriorityTest.h>
#include <string>

class UnitCategory {
public:
	UnitCategory(int categoryId);
	virtual ~UnitCategory();

	bool isValid() const;

	int categoryId;
	std::string name;

	PriorityTest* test;
};

template<class OStream>
OStream& operator<<(OStream& out, const UnitCategory& cat) {
	out<<"UnitCategory( \n";
	out<<"\t"<<"categoryId="<<cat.categoryId<<"\n";
	out<<"\t"<<"test="<<cat.test<<"\n";
	out<<")\n";
    return out;
}

#endif