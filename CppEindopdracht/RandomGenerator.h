#pragma once
#include <random>

class RandomGenerator
{
public:
	static RandomGenerator *s_instance;

	RandomGenerator();
	~RandomGenerator();

	static RandomGenerator *instance();

	int randomNumber(int min, int max);
private:
	std::default_random_engine* generator_;
};

