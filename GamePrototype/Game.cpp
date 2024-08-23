#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <ctime>
#include "Ballon.h"
#include "Square.h"
#include "Entity.h"
#include <iostream>
#include "time.h"
using namespace utils;
using namespace std;

Game::Game( const Window& window ) 
	:BaseGame{ window }, TerritoryWidth(150),EnemyTerritory(50)
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	radMax = TerritoryWidth / 2;
	radMin = TerritoryWidth / 5;
	srand(static_cast<unsigned int>(time(nullptr)));
	Ballon* B = new Ballon(this,Point2f(50, 50), 30, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	Entitys.push_back(B);
	Ballon* A = new Ballon(this, Point2f(50, 200), 40, Color4f(1.5f, 1.2f, 0.6f, 0.7f));
	Entitys.push_back(A);
	
	int BallsCount = 0;

	srand((unsigned)time(NULL));
	
	bool isBallsGenerated = true;
	srand(maxBalls - minBalls);
	numBalls = round( (float)rand()/RAND_MAX * (maxBalls - minBalls) + minBalls);
	std::cout << (float)rand() / RAND_MAX << std::endl;
	std::cout << numBalls << std::endl;
	
	while (isBallsGenerated) {
		bool isOverlap = false;
		//[H - EnemyTerritory - R, EnemyTerritory+r]
		float NewBallR = ((float)rand() / RAND_MAX) * (radMax - radMin) + radMin;
		float maxY = GetViewPort().height - EnemyTerritory - NewBallR;
		float minY = EnemyTerritory + NewBallR;

		float NewBallY = ((float)rand() / RAND_MAX) * (maxY - minY) + minY;

		float NewBallAlpha = ((float)rand() / RAND_MAX) * (1 - 0.3) + 0.3;

		Ballon* n = new Ballon(this, Point2f{ TerritoryWidth / 2,NewBallY }, NewBallR, Color4f{ 1,1,1,NewBallAlpha });
		
		for (auto& e : Entitys) {

			float r = dynamic_cast<Ballon*>(e)->getR();
			float y = e->GetPosition().y;

			float R = n->getR();
			float Y = n->GetPosition().y;

			if ((y+r <= Y-R) || (y-r >= Y+R)) {
				isOverlap = true;
				break;
			}
		}
		if (isOverlap) continue;
		
		Entitys.push_back(n);
		BallsCount++;
		if (BallsCount == numBalls) {
			isBallsGenerated = false;
		}
		


	}
	m_CurrentBallon = (Ballon*)(Entitys[1]);

	Square* S1 = new Square(this, Point2f(GetViewPort().width / 2 - 250, GetViewPort().height), 50, Color4f(1.0f, 0.0f, 0.0f, 1.0f),1.0f);
	Entitys.push_back(S1);
	Square* S2 = new Square(this, Point2f(GetViewPort().width / 2 + 250, GetViewPort().height), 50, Color4f(0.0f, 1.0f, 0.0f, 1.0f),2.0f);
	Entitys.push_back(S2);
	Square* S3 = new Square(this, Point2f(GetViewPort().width / 2 - 125, GetViewPort().height), 50, Color4f(0.0f, 1.0f, 0.0f, 1.0f),3.0f);
	Entitys.push_back(S3);
	Square* S4 = new Square(this, Point2f(GetViewPort().width / 2 + 75, GetViewPort().height), 50, Color4f(0.0f, 1.0f, 0.0f, 1.0f),4.0f);
	Entitys.push_back(S4);
	Square* S5 = new Square(this, Point2f(GetViewPort().width / 2 - 37, GetViewPort().height), 50, Color4f(0.0f, 1.0f, 0.0f, 1.0f),5.0f);
	Entitys.push_back(S5);
	

	Entitys[1]->SetState(Entity::State::Moving);
	Entitys[2]->SetState(Entity::State::Moving);
	Entitys[3]->SetState(Entity::State::Moving);
	Entitys[7]->SetState(Entity::State::Moving);
	Entitys[6]->SetState(Entity::State::Moving);
	Entitys[8]->SetState(Entity::State::Moving);
	Entitys[9]->SetState(Entity::State::Moving);
	Entitys[10]->SetState(Entity::State::Moving);
}

void Game::Cleanup( )
{
	for (auto& Entity: Entitys) 
	{
		delete Entity;
		Entity = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	for (int i = getNumpofBalls(); i < 4; Entitys.size()) {
		if ( (dynamic_cast<Square*>(Entitys[i]))->IsHitting(m_CurrentBallon) ) {
			m_CurrentBallon->SetState(Entity::State::Dead);
		}
		
	}
	
	for (auto& entity : Entitys)
	{
		entity->Update(elapsedSec);

		
		Ballon* ballon = dynamic_cast<Ballon*>(entity);
		if (ballon && ballon->HasExited())
		{
			ballon->SetState(Entity::State::Calm); 
		}
	}

}

int Game::getNumpofBalls() {
	return numBalls;
}

void Game::Draw( ) const
{
	 
	ClearBackground( );
	GameField();
	for (auto& entity : Entitys)
	{
		entity->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (m_CurrentBallon != nullptr)
	{
		switch (e.keysym.sym)
		{
		case SDLK_UP:
			
			m_CurrentBallon->SetPosition(Point2f{ m_CurrentBallon->GetPosition().x, m_CurrentBallon->GetPosition().y + 10.0f });
			break;
		case SDLK_DOWN:
			
			m_CurrentBallon->SetPosition(Point2f{ m_CurrentBallon->GetPosition().x, m_CurrentBallon->GetPosition().y - 10.0f });
			break;
		}
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::GameField() const
{
	
	SetColor(Color4f{ 0.8f, 0.8f, 0.8f, 1.0f });

	
	DrawLine(TerritoryWidth, 0, TerritoryWidth, GetViewPort().height, 2.0f);
	DrawLine( TerritoryWidth , EnemyTerritory, GetViewPort().width  - TerritoryWidth , EnemyTerritory, 2.0f);
	DrawLine( TerritoryWidth , GetViewPort().height - EnemyTerritory, GetViewPort().width  - TerritoryWidth , GetViewPort().height - EnemyTerritory, 2.0f);
	
	DrawLine(GetViewPort().width - TerritoryWidth, 0, GetViewPort().width-TerritoryWidth, GetViewPort().height, 2.0f);
	
}
