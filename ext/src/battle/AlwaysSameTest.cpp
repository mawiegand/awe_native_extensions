#include <AlwaysSameTest.h>

AlwaysSameTest::AlwaysSameTest() {

}

void AlwaysSameTest::pushCategoryToPriority(int category) {
	priority.push_back(category);
}

const std::vector<int>& AlwaysSameTest::test(const Battle& battle) const {
	return priority;
}
