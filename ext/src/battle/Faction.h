#ifndef WackBattle_Faction_h
#define WackBattle_Faction_h

#include <Army.h>
#include <TestResult.h>

class Faction {
public:
	Faction();
	virtual ~Faction();
	
	bool isValid() const;
	
	void addArmy(Army* army);
	size_t numArmies() const;
	Army* getArmy(size_t i);
	
	size_t startSize() const;
	size_t startSizeOfCategory(int category) const;
	bool hasOfUnitsCategory(int category) const;
	
	TestResult* getTestResult(size_t i);
	size_t testResultsSize() const;
	
	Army* combinedArmy();
	
	std::vector<Army*> armies;
	std::map<int, TestResult*> testResults;
};

template<class OStream>
OStream& operator<<(OStream& out, const Faction& faction) {
	out<<"Faction( \n";
	out<<"\t"<<"armies="<<"\n";
	std::vector<Army*>::const_iterator it;
	for (it = faction.armies.begin(); it != faction.armies.end(); it++) {
		out<<(*(*it))<<"\n";
	}
	out<<")\n";
    return out;
}

#endif
