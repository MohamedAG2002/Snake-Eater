#include "Util.h"

#include <random>

float utl::Clamp(float value, float min, float max)
{
	if (value > max) return value = max;
	else if (value < min) return value = min;
	else return value;
}

int utl::GetRand(int min, int max)
{
	int rand = 0;

	// The seed generator
	std::random_device randDevice;
	
	// Helps generate the random number between the given min and max
	std::default_random_engine randEngine(randDevice());
	std::uniform_int_distribution<int> uniformDist(min, max);
	rand = uniformDist(randEngine);

	return rand;
}