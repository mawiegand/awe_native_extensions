#ifndef WackBattle_Units_h
#define WackBattle_Units_h

#include <cstddef>
#include <string>

class Units {
public:
	Units();
	
	bool valid() const;
	
#pragma mark unit state information
	size_t numUnitsAtStart;
	size_t numDeaths;
	size_t numHits;
	size_t numKills;
	double newXp;
#pragma mark -

#pragma mark unit type information
	int unitTypeId;
	int unitCategoryId;
	///name the name of the type
	std::string name;
	
	///damage the amount of damage that this unit type deals per unit
	double baseDamage;
	///criticalDamage the amount of extra damage that is beeing dealt by a unit if a critical hit happens
	double criticalDamage;
	///criticalProbability the probability for a unit of this type to execute a critical strike
	double criticalProbability;
	///attackerBonusDamage the additional amount of damage that a unit of this type deals if it is in an attacking force
	double attackerBonusDamage;
	
	///hitpoints the amount of healthpoints that each unit of this type has
	double hitpoints;
	///
	double armor;
	///
	double xpFactorPerUnit;
#pragma mark -
};

#endif