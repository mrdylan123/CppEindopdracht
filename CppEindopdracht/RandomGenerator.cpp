#include "RandomGenerator.h"
#include <ctime>

RandomGenerator *RandomGenerator::s_instance = nullptr;

RandomGenerator::RandomGenerator()
{
	generator_ = new std::default_random_engine;
	generator_->seed(time(nullptr));
}


RandomGenerator::~RandomGenerator()
{
	delete generator_;
}

RandomGenerator* RandomGenerator::instance()
{
	if (!s_instance)
		s_instance = new RandomGenerator;
	return s_instance;
}

int RandomGenerator::randomNumber(const int min, const int max)
{
	const std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator_);
}
