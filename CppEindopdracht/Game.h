#pragma once

class HeroLoader;
class Dungeon;
class Hero;

class Game
{
public:
	Game();
	~Game();
	Game(const Game& other) = delete;
	Game(Game&& other) noexcept = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) noexcept = delete;

	void start() const;
private:
	Dungeon* dungeon_;
	HeroLoader* heroLoader_;

	Hero* newHero() const;
};

