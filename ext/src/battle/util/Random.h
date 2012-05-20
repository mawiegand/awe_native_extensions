#ifndef WakBattle_util_Random_h
#define WakBattle_util_Random_h

#include <cstdlib>
#include <vector>
#include "ErrorHandling.h"
namespace util {
class Random {
public:
	static double random();
	static bool random(double probability);
	static double random01(double probability);
	static size_t random(size_t start, size_t end);
	
	template<typename T>
	static void shuffle(std::vector<T>& vector);
};

template<typename T>
void Random::shuffle(std::vector<T>& vector) {
	logMessage("RANDOM:SHUFFLE");
	for (size_t i = 0; i < vector.size(); i++) {
        logMessage("RANDOM:SHUFFLE loop : "  << i);
		size_t newPos = random(0, vector.size()-1);
		logMessage("RANDOM:SHUFFLE newPos : "  << newPos);
		T oldVar = vector[newPos];
		vector[newPos] = vector[i];
		vector[i] = oldVar;
	}
	logMessage("RANDOM:SHUFFLE END");
}

} //namespace util
#endif
