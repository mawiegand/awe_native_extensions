#include <Unit.h>

#include <util/ErrorHandling.h>
#include <util/MemoryManagement.h>
#include <Battle.h>
#include <Army.h>
#include <math.h>
#include <util/Random.h>
#include <sstream>
#include <cmath>

using namespace std;

#define MAX(a,b)   ((a) > (b) ? (a) : (b))

int Unit::numReferences = 0;

bool Unit::initiativeGreater(const Unit* a, const Unit* b) {
	awePtrCheck(a);
	awePtrCheck(b);
	return (a->initiative > b->initiative);
}

Unit::Unit() : 
	numUnitsAtStart(0),
	numDeaths(0),
	numHits(0),
	numKills(0),
	newXp(0),
	unitTypeId(-1),
	unitCategoryId(-1),
	name(),
	damageTaken(0),
	damageInflicted(0),
	baseDamage(0),
	criticalDamage(0),
	criticalProbability(0),
	initiative(0),
	effectiveness(),
	hitpoints(0),
	armor(0),
	xpFactorPerUnit(0)
{
	numReferences++;
	//logMessage("CONSTRUCTION Unit ref="<<numReferences);
	
}

Unit::Unit(const Unit& other) :
	numUnitsAtStart(other.numUnitsAtStart),
	numDeaths(other.numDeaths),
	numHits(other.numHits),
	numKills(other.numKills),
	newXp(other.newXp),
	damageLogs(),
	unitTypeId(other.unitTypeId),
	unitCategoryId(other.unitCategoryId),
	name(other.name),
	damageTaken(other.damageTaken),
	damageInflicted(other.damageInflicted),
	baseDamage(other.baseDamage),
	criticalDamage(other.criticalDamage),
	criticalProbability(other.criticalProbability),
	initiative(other.initiative),
	effectiveness(other.effectiveness),
	hitpoints(other.hitpoints),
	armor(other.armor),
	xpFactorPerUnit(other.xpFactorPerUnit)
{
	numReferences++;
	//logMessage("COPY CONSTRUCTION Unit ref="<<numReferences);
}

Unit::~Unit() {
	numReferences--;
	//logMessage("DECONSTRUCTION Unit ref="<<numReferences);
}

bool Unit::isValid() const {
	return unitTypeId >= 0 && unitCategoryId >= 0 && numUnitsAtStart >= numDeaths;
}

static double estimate_hit_probability(double att, double def)
{
  util::Random rand = util::Random();
  unsigned int repititions = 100;
  int hits = 0;
  for (unsigned int i=0; i < repititions; i++) {
    hits += floor(rand.random() * att) /* +1 */ > floor(rand.random() * def) /* +1 */  ? 1 : 0 ;
  }
  return hits / (1.0 * repititions);
}

double Unit::numDeadUnits(double numHitting, double superiorityBonus, double currentEffectiveness, Unit* target) const {
  double att       = baseDamage * (currentEffectiveness + superiorityBonus);
  double def       = target->armor;
  double hitChance = estimate_hit_probability(att, def);

  double damage    = baseDamage;  // add damage modifiers here, as soon as available
	return ((criticalDamage*criticalProbability) + (damage*hitChance))/(target->hitpoints) * numHitting;
}

void Unit::applyDamage(double superiorityBonus, Army* targets) {
	//add damage log vector
	damageLogs.push_back(std::vector<DamageLog*>());
	std::vector<DamageLog*>& logs = damageLogs.back();
	//damage calculation
	double numTargetsAlive = ((double) targets->numUnitsAlive());
	double pFactor = (((double) numUnitsAtStart) - ((double) numHits))/numTargetsAlive; 
	std::vector<Unit*>::iterator targetIt;
	for (targetIt = targets->units.begin(); targetIt != targets->units.end(); targetIt++) {
		//logMessage("\t\t\t\ttarget type_id="<<(*targetIt)->unitTypeId);
		//create damage log
		DamageLog* log = new DamageLog();
		logs.push_back(log);
		awe::MemoryManagement::registerNewObject(log);
		//aweRegisterNewObject(log, DamageLog);
		#ifdef SWIG
		//swig_type_info asdf;
		//SWIG_NewPointerObj((void*)log, SWIGTYPE_p_DamageLog, SWIG_POINTER_OWN);
		#endif
		//fill with values
		log->targetId = (*targetIt)->unitTypeId;
		log->targetUnitCategoryId = (*targetIt)->unitCategoryId;
		log->superorityBonus = superiorityBonus;
	
		double numHittingUnits = (((double) (*targetIt)->numUnitsAtStart) - ((double) (*targetIt)->numDeaths)) *pFactor;
		log->numHittingUnits = numHittingUnits;
		
		//get effectiveness
		double currentEffectiveness = getEffectivenessFor((*targetIt)->unitCategoryId);
		log->effectiveness = currentEffectiveness;
		
		double deaths = numDeadUnits(numHittingUnits, superiorityBonus, currentEffectiveness, *targetIt);
		//overkill
		/*logMessage("numHittingUnits:");
		logMessage(numHittingUnits);*/
		//logMessage("DEATHS="<<deaths);
		if (deaths + ((double)(*targetIt)->numDeaths) > (*targetIt)->numUnitsAtStart) {
			//log->overkill = true;
			damageInflicted += ((*targetIt)->numUnitsAtStart-(*targetIt)->numDeaths)*(*targetIt)->hitpoints;
			//damageInflicted += deaths * (*targetIt)->hitpoints;
			numKills += ((*targetIt)->numUnitsAtStart-(*targetIt)->numDeaths);
			/*logMessage("\t\t\t\toverkill");
			logMessage("\t\t\t\tkilled += "<<((*targetIt)->numUnitsAtStart-(*targetIt)->numDeaths));*/
			
			//callculate the hits that are left
			//1 - living/Tote = Überschlag
			double overkill = 1.0-(((*targetIt)->numUnitsAtStart-(*targetIt)->numDeaths)/deaths);
			numHits +=  (numHittingUnits-(overkill*numHittingUnits));
			//logMessage("\t\t\t\numHits += "<<(numHittingUnits-(overkill*numHittingUnits)));
			
			(*targetIt)->numDeaths = (*targetIt)->numUnitsAtStart;
			(*targetIt)->damageTaken = (*targetIt)->numUnitsAtStart * (*targetIt)->hitpoints;
			(*targetIt)->newXp = ((double)(*targetIt)->numUnitsAtStart) * (*targetIt)->xpFactorPerUnit;
		//all damage has been dealt
		} else {
			//logMessage("\t\t\t\tpartialkill");
			log->overkill = false;
			damageInflicted += deaths * (*targetIt)->hitpoints;
			//logMessage("\t\t\t\tpre deaths="<<deaths);
			double p = deaths-floor(deaths);
			log->restProbability = p;
			if (p > 0.0) {
				//logMessage("\t\t\t\texperiment with p="<<p);
				if (util::Random::random(p)) {
					//logMessage("\t\t\t\texperiment success");
					log->experimentSuccess = true;
					deaths = ceil(deaths);
					
				} else {
					//logMessage("\t\t\t\texperiment failure");
					log->experimentSuccess = false;
					deaths = floor(deaths);
				}
			}
			//logMessage("\t\t\t\tfinal deaths="<<deaths);
			numKills += (size_t)deaths;
			numHits += numHittingUnits;
			(*targetIt)->numDeaths += deaths;
			(*targetIt)->damageTaken += deaths * (*targetIt)->hitpoints;
			(*targetIt)->newXp += deaths * (*targetIt)->xpFactorPerUnit;
		}
		
	}
	
}

void Unit::setEffectivenessFor(int type, double value) {
	effectiveness[type] = value;
}
double Unit::getEffectivenessFor(int type) const {
	std::map<int, double>::const_iterator it = effectiveness.find(type);
	if (it != effectiveness.end()) {
		return it->second;
	}
	aweError("missing effectiveness value for type ");
  return 1.0;
}

void Unit::resetDamageLogs() {
	damageLogs.clear();
}

size_t Unit::numDamageLogs() const {
	return damageLogs.size();
}
size_t Unit::numSubDamageLogs(size_t i) const {
	if (i >= damageLogs.size()) {
		aweError("out of bounds");
	}
	return damageLogs[i].size();
}
DamageLog* Unit::getDamageLog(size_t i, size_t subI) {
	if (i >= damageLogs.size()) {
		aweError("out of bounds");
	}
	if (subI >= damageLogs[i].size()) {
		aweError("out of bounds");
	}
	return damageLogs[i][subI];
}
