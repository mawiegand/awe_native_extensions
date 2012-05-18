#ifndef WackBattle_PriorityTest_h
#define WackBattle_PriorityTest_h

#include <vector>
#include <iostream>

class Battle;
class Faction;

class PriorityTest {
public:
	virtual ~PriorityTest() {}
	virtual const std::vector<int>& test(const Faction* myFaction, const Battle& battle) const = 0;
	
  virtual std::ostream& toString(std::ostream& out) const = 0;
};



template<class OStream>
OStream& operator<<(OStream& out, const PriorityTest& test) {
  return test.toString(out);
}

#endif
