#include <LineSizeTest.h>

LineSizeTest::LineSizeTest() {

}
void LineSizeTest::pushCategoryToPriorityOnFail(int category) {
	prioritiesOnFail.push_back(category);
}
void LineSizeTest::pushCategoryToPriorityOnSuccess(int category) {
	prioritiesOnSuccess.push_back(category);
}
const std::vector<int>& LineSizeTest::test(const Battle& battle) const {
	///TODO
	return this->prioritiesOnFail;
}