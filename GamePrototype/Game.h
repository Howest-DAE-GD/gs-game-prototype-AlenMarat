#pragma once
#include "pch.h"
#include "BaseGame.h"
#include <vector>
#include "Entity.h"
#include "Texture.h"

class Ballon;

class Game : public BaseGame
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update(float elapsedSec) override;
	void Draw() const override;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;
	int getNumpofBalls();
	float getTerrWidth();
	bool goNextBallon();
	int NumSurvived();
	float getEnemyTerritoryWidth();
	int NumDead();
	float getAbsoluteTime();
	void InitEnemy();
	void InitBalls();
	int getLevel();
private:
	int enCount;
	bool blockKeys;
	float radMax;
	float radMin;
	int maxBalls = 4;
	int minBalls = 4;
	float MaxVelocity = 250;
	float MinVelocity = 150;
	int numBalls;
	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void GameField() const;
	float TerritoryWidth;
	std::vector<Entity*>Entitys;
	Ballon* m_CurrentBallon;
	float EnemyTerritory;
	//Texture* m_scoreTexture{};
	Texture* m_LeftBalls;
	Texture* m_EscapedBalls;
	Texture* m_GOTexture;
	float m_AbsoluteTime;
	int LevelNum;

};