#include <CavalryTest.h>

CavalryTest::CavalryTest() {

}
void CavalryTest::pushCategoryToPriorityForFlankFail(int category) {
	priorityForFlankFail.push_back(category);
}
void CavalryTest::pushCategoryToPriorityForFlankSuccess(int category) {
	priorityForFlankSuccess.push_back(category);
}
const std::vector<int>& CavalryTest::test(const Battle& battle) const {
	return this->priorityForFlankFail;
}