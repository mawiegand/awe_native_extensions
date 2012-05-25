#ifndef WackBattle_Unit_h
#define WackBattle_Unit_h

#include <cstddef>
#include <string>
#include <map>
#include <vector>
#include <DamageLog.h>

class Battle;
class Army;

class Unit {
public:
	static bool initiativeGreater(const Unit* a, const Unit* b);
	static int numReferences;
public:
	Unit();
	Unit(const Unit& other);
	virtual ~Unit();
	
	bool isValid() const;
	
	double numDeadUnits(double numHits, double superiorityBonus, double currentEffectiveness, Unit* target) const;
	void applyDamage(double superiorityBonus, Army* targets);
	
	void setEffectivenessFor(int type, double value);
	double getEffectivenessFor(int type) const;
	
	void resetDamageLogs();
	size_t numDamageLogs() const;
	size_t numSubDamageLogs(size_t i) const;
	DamageLog* getDamageLog(size_t i, size_t subI);
	
#pragma mark unit state information
	size_t numUnitsAtStart;
	size_t numDeaths;
	double numHits;
	size_t numKills;
	double newXp;
	std::vector<std::vector<DamageLog*> > damageLogs;
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
	std::map<int, double> effectiveness;
	
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
	out<<"\t"<<"unitTypeId="<<unit.unitTypeId<<"\n";
	out<<"\t"<<"unitCategoryId="<<unit.unitCategoryId<<"\n";
	out<<"\t"<<"name="<<unit.name<<"\n";
	out<<"\t"<<"damageTaken="<<unit.damageTaken<<"\n";
	out<<"\t"<<"damageInflicted="<<unit.damageInflicted<<"\n";
	out<<"\t"<<"baseDamage="<<unit.baseDamage<<"\n";
	out<<"\t"<<"criticalDamage="<<unit.criticalDamage<<"\n";
	out<<"\t"<<"criticalProbability="<<unit.criticalProbability<<"\n";
	out<<"\t"<<"initiative="<<unit.initiative<<"\n";
	out<<"\t"<<"effectiveness={\n";

	{
		std::map<int, double>::const_iterator it;
		for (it = unit.effectiveness.begin(); it != unit.effectiveness.end(); it++) {
			out <<"\t\t"<<it->first<<" => "<<it->second<<"\n";
		}
	}
	out<<"\t"<<"}\n";
	out<<"\t"<<"hitpoints="<<unit.hitpoints<<"\n";
	out<<"\t"<<"armor="<<unit.armor<<"\n";
	out<<"\t"<<"xpFactorPerUnit="<<unit.xpFactorPerUnit<<"\n";
	out<<")\n";
    return out;
}

#endif
