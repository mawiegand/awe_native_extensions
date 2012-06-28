#include <LineSizeTest.h>

#include <Battle.h>
#include <math.h>
#include <util/Random.h>
#include <util/ErrorHandling.h>
#include <sstream>

LineSizeTest::LineSizeTest(int testCategoryId) :  
	testCategoryId(testCategoryId),
	minProportion(1.0),
	minExponent(2.0),
	minFactor(0.3),
	normalFactor(0.5),
	normalReduction(0.2),
	maxPropotion(2.0),
	maxProbability(0.8) ///TODO missing in Wiki
{
	//logMessage("CONSTRUCTOR LineSizeTest");
}
LineSizeTest::~LineSizeTest() {
	//logMessage("DECONSTRUCTION LineSizeTest");
}
void LineSizeTest::pushCategoryToPriorityOnFail(int category) {
	prioritiesOnFail.push_back(category);
}
void LineSizeTest::pushCategoryToPriorityOnSuccess(int category) {
	prioritiesOnSuccess.push_back(category);
}
const std::vector<int>& LineSizeTest::test(const Faction* myFaction, const Battle& battle, TestResult& result) const {

	//logMessage("LINE SIZE TEST TEST");
	result.testType = "LineSizeTest";

	size_t enemiesOfCategory = battle.enemyFactionsStartSizeOfCategory(testCategoryId, myFaction);
	if (enemiesOfCategory <= 0) {
		result.passed = true;
		result.debugText = "success based on enemiesOfCategory";
		return prioritiesOnSuccess;
	}
	
	size_t myOfCategory = myFaction->startSizeOfCategory(testCategoryId);
	if (myOfCategory <= 0) {
		result.passed = false;
		result.debugText = "failed based on myOfCategory";
		return prioritiesOnFail;
	}
	
	double propotion = ((double) enemiesOfCategory) / ((double) myOfCategory);
	//logMessage("proportion="<<propotion);
	
	double p = maxProbability;
	if (propotion < minProportion) {
		p = pow(propotion, minExponent) * minFactor;
	} else if (propotion <= maxPropotion) {
		p = normalFactor*propotion - normalReduction;
	}
	
	if (util::Random::random(p)) {
		result.passed = true;
		{
			std::stringstream sstr;
			sstr<<"success based on experiment (p="<<p<<", proportion="<<propotion<<")";
			result.debugText = sstr.str();
		}
		return this->prioritiesOnSuccess;
	}
	{
		std::stringstream sstr;
		sstr<<"failed based on experiment (p="<<p<<", proportion="<<propotion<<")";
		result.debugText = sstr.str();
	}
	result.passed = false;
	
	return this->prioritiesOnFail;
	
}


std::ostream& LineSizeTest::toString(std::ostream& out)  const
{
  out << "LineSizeTest: Success:";
  for (unsigned int i=0; i < prioritiesOnSuccess.size(); i++) {
    out << " " << prioritiesOnSuccess[i];
  }
  out << " Fail:";
  for (unsigned int i=0; i < prioritiesOnFail.size(); i++) {
    out << " " << prioritiesOnFail[i];
  }
  return out ;
}