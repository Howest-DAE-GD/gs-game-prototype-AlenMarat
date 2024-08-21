#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <ctime>
#include "Ballon.h"
#include "Square.h"
#include "Entity.h"
using namespace utils;

Game::Game( const Window& window ) 
	:BaseGame{ window }, TerritoryWidth(150)
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	//srand(static_cast<unsigned int>(time(nullptr)));
	Ballon* B = new Ballon(this,Point2f(50, 50), 30, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	Entitys.push_back(B);
	Ballon* A = new Ballon(this, Point2f(50, 200), 40, Color4f(1.5f, 1.2f, 0.6f, 0.7f));
	Entitys.push_back(A);
	
	m_CurrentBallon = (Ballon*)(Entitys[1]);

	Square* S1 = new Square(this, Point2f(GetViewPort().width / 2, GetViewPort().height / 2), 50, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	Entitys.push_back(S1);
	Square* S2 = new Square(this, Point2f(GetViewPort().width / 2 , GetViewPort().height / 2 + 100), 50, Color4f(0.0f, 1.0f, 0.0f, 1.0f));
	Entitys.push_back(S2);

	Entitys[1]->SetState(Entity::State::Moving);


	Entitys[2]->SetState(Entity::State::Moving);
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
	for (int i = 2; i < 4; i++) {
		if ( (dynamic_cast<Square*>(Entitys[i]))->IsHitting(m_CurrentBallon) ) {
			m_CurrentBallon->SetState(Entity::State::Dead);
		}
		
	}
	
	for (auto& entity : Entitys)
	{
		entity->Update(elapsedSec);
	}
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
	DrawLine(GetViewPort().width / 2 - TerritoryWidth / 2, 0, GetViewPort().width / 2 - TerritoryWidth / 2, GetViewPort().height, 2.0f);
	DrawLine(GetViewPort().width / 2 + TerritoryWidth / 2, 0, GetViewPort().width / 2 + TerritoryWidth / 2, GetViewPort().height, 2.0f);
	
	DrawLine(GetViewPort().width - TerritoryWidth, 0, GetViewPort().width-TerritoryWidth, GetViewPort().height, 2.0f);
	
}
