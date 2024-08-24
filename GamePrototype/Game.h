#pragma once
#include "pch.h"
#include "BaseGame.h"
#include <vector>
#include "Entity.h"

class Ballon;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
	int getNumpofBalls();
	float getTerrWidth();

private:
	float radMax;
	float radMin;
	int maxBalls = 1;
	int minBalls = 1;
	int numBalls;
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void GameField() const;
	float TerritoryWidth;
	std::vector<Entity*>Entitys;
	Ballon* m_CurrentBallon;
	float EnemyTerritory;
	
};