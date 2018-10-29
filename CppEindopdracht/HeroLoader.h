#pragma once
class Hero;

class HeroLoader
{
public:
	HeroLoader();
	~HeroLoader();
	HeroLoader(const HeroLoader& other) = delete;
	HeroLoader(HeroLoader&& other) noexcept = delete;
	HeroLoader& operator=(const HeroLoader& other) = delete;
	HeroLoader& operator=(HeroLoader&& other) noexcept = delete;

	bool showSavedHeroes() const;

	Hero* loadHero(int index) const;
	void saveHero(Hero* hero) const;
};

