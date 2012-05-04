#ifndef WakBattle_util_Random_h
#define WakBattle_util_Random_h

#include <cstdlib>
#include <vector>

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
	for (size_t i = 0; i < vector.size(); i++) {
		size_t newPos = random(0, vector.size()-1);
		T oldVar = vector[newPos];
		vector[newPos] = vector[i];
		vector[i] = oldVar;
	}
}

} //namespace util
#endif
