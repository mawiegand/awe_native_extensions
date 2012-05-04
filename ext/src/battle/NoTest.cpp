#include <NoTest.h>

NoTest::NoTest() {

}

void NoTest::pushCategoryToPriority(int category) {
	priorities.push_back(category);
}

const std::vector<int>& NoTest::test(const Battle& battle) const {
	return priorities;
}
