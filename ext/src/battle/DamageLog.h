#ifndef awe_native_extensions_DamageLog_h
#define awe_native_extensions_DamageLog_h

class DamageLog {
public:
	DamageLog();
	virtual ~DamageLog();
	
	int targetId;
	int targetUnitCategoryId;
	double effectiveness;
	bool overkill;
	double numHits;
	double numHittingUnits;
	double superorityBonus;
	double numKills;
	double restProbability;
	bool experimentSuccess;
};

#endif
