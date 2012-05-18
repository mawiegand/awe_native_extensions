#include <NoTest.h>

#include <util/ErrorHandling.h>

NoTest::NoTest() {

}

NoTest::~NoTest() {
	logMessage("DECONSTRUCTION NoTest");
}

void NoTest::pushCategoryToPriority(int category) {
	priorities.push_back(category);
}

const std::vector<int>& NoTest::test(const Faction* myFaction, const Battle& battle) const {
	return priorities;
}

  
std::ostream& NoTest::toString(std::ostream& out)  const
{
  out << "NoTest: ";
  for (unsigned int i=0; i < priorities.size(); i++) {
    out << " " << priorities[i];
  }
  return out ;
}