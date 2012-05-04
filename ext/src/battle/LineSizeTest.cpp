#include <LineSizeTest.h>

#include <Battle.h>

LineSizeTest::LineSizeTest(int testCategoryId) :  testCategoryId(testCategoryId) {

}
void LineSizeTest::pushCategoryToPriorityOnFail(int category) {
	prioritiesOnFail.push_back(category);
}
void LineSizeTest::pushCategoryToPriorityOnSuccess(int category) {
	prioritiesOnSuccess.push_back(category);
}
const std::vector<int>& LineSizeTest::test(const Faction* myFaction, const Battle& battle) const {

	size_t enemiesOfCategory = battle.enemyFactionsStartSizeOfCategory(testCategoryId, myFaction);
	if (enemiesOfCategory <= 0) {
		return prioritiesOnSuccess;
	}
	size_t myOfCategory = myFaction->startSizeOfCategory(testCategoryId);
	if (myOfCategory <= 0) {
		return prioritiesOnFail;
	}
	

	return this->prioritiesOnFail;
	
}