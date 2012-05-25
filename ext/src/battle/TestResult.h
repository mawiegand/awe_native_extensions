#ifndef WackBattle_TestResult_h
#define WackBattle_TestResult_h

#include <string>

class TestResult {
public:
	TestResult();
	bool passed;
	std::string testType;
	std::string debugText;
};

#endif
