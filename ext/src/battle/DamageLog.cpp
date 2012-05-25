#include <DamageLog.h>

#include <util/ErrorHandling.h>

DamageLog::DamageLog() :
	targetId(-1),
	targetUnitCategoryId(-1),
	effectiveness(0.0),
	overkill(false),
	numHits(0.0),
	numHittingUnits(0.0),
	superorityBonus(0),
	numKills(0.0),
	restProbability(0.0),
	experimentSuccess(false)
{

}
DamageLog::~DamageLog() {

	logMessage("DECONSTRUCTION DamageLog");
}
