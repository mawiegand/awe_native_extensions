#include <Units.h>

Units::Units() : 
	numUnitsAtStart(0),
	numDeaths(0),
	numHits(0),
	numKills(0),
	newXp(0),
	unitTypeId(-1),
	unitCategoryId(-1)
{

}

bool Units::valid() const {
	return unitTypeId >= 0 && unitCategoryId >= 0;
}