#pragma once
#include <random>

class RandomGenerator
{
public:
	static RandomGenerator *s_instance;

	~RandomGenerator();
	RandomGenerator(const RandomGenerator& other) = delete;
	RandomGenerator(RandomGenerator&& other) noexcept = delete;
	RandomGenerator& operator=(const RandomGenerator& other) = delete;
	RandomGenerator& operator=(RandomGenerator&& other) noexcept = delete;

	static RandomGenerator *instance();

	/**
	 * \brief Generates a random number between min and max
	 * \param min Minimum number to generate
	 * \param max Maximum number to generate
	 * \return The randomly generated number
	 */
	int randomNumber(int min, int max) const;
private:
	RandomGenerator();
	std::default_random_engine* generator_;
};

