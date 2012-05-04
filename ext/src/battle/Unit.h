#ifndef WackBattle_Unit_h
#define WackBattle_Unit_h

#include <cstddef>
#include <string>

class Battle;
class Army;

class Unit {
public:
	static bool initiativeGreater(const Unit* a, const Unit* b);
public:
	Unit();
	
	bool valid() const;
	
	double numDeadUnits(double numHits, double superiorityBonus, Unit* target) const;
	void applyDamage(double superiorityBonus, Army* targets);
	
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
	
	double damageTaken;      ///< sum of hitpoints lost in this unit (type)
	double damageInflicted;  ///< sum of hitpoints destoyed at opposing units
	
	///damage the amount of damage that this unit type deals per unit
	double baseDamage;
	///criticalDamage the amount of extra damage that is beeing dealt by a unit if a critical hit happens
	double criticalDamage;
	///criticalProbability the probability for a unit of this type to execute a critical strike
	double criticalProbability;
	
	int initiative; ///< initiative of unit, determines sequence of attackers 
	
	///hitpoints the amount of healthpoints that each unit of this type has
	double hitpoints;
	///
	double armor;
	///
	double xpFactorPerUnit;
#pragma mark -
};

template<class OStream>
OStream& operator<<(OStream& out, const Unit& unit) {
	out<<"Unit( \n";
	out<<"\t"<<"numUnitsAtStart="<<unit.numUnitsAtStart<<"\n";
	out<<"\t"<<"numDeaths="<<unit.numDeaths<<"\n";
	out<<"\t"<<"numHits="<<unit.numHits<<"\n";
	out<<"\t"<<"numKills="<<unit.numKills<<"\n";
	out<<"\t"<<"newXp="<<unit.newXp<<"\n";
	out<<"\t"<<"name="<<unit.name<<"\n";
	out<<"\t"<<"damageTaken="<<unit.damageTaken<<"\n";
	out<<"\t"<<"damageInflicted="<<unit.damageInflicted<<"\n";
	out<<"\t"<<"baseDamage="<<unit.baseDamage<<"\n";
	out<<"\t"<<"criticalDamage="<<unit.criticalDamage<<"\n";
	out<<"\t"<<"criticalProbability="<<unit.criticalProbability<<"\n";
	out<<"\t"<<"initiative="<<unit.initiative<<"\n";
	out<<"\t"<<"hitpoints="<<unit.hitpoints<<"\n";
	out<<"\t"<<"armor="<<unit.armor<<"\n";
	out<<"\t"<<"xpFactorPerUnit="<<unit.xpFactorPerUnit<<"\n";
	out<<")\n";
    return out;
}

#endif
