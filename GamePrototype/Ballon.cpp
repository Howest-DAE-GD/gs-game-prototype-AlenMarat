#include "utils.h"
#include"Ballon.h"
#include <vector>
#include "pch.h"
#include "Game.h"
using namespace utils;

Ballon::Ballon(Game* game, Point2f start_point,  float Radius, Color4f BC)
	:Entity(game, start_point), BallonColor{ BC }, Radius{Radius}, m_HasExited{ false }
	
{
	m_Geometry = Circlef{ start_point, Radius };
	m_PrevState = Entity::State::Dead;
	m_Velocity = Vector2f(130,0);
}
float Ballon::getR() {
	return Radius;
}

void Ballon::Update(float elapsedSec)
{
	switch (m_CurrentState) 
	{
	case Entity::State::Moving:
		{
			m_CurrentPoint.x += m_Velocity.x * elapsedSec;
			m_CurrentPoint.y += m_Velocity.y * elapsedSec;
			//float leftBoundary = m_pGame->GetViewPort().width / 2 - 250; // ??? ???? ???????? ???????
			float rightBoundary = m_pGame->GetViewPort().width / 2 + 550; // ??? ???? ???????? ???????

			// ????????, ????????? ?? ??? ?? ????????? ????
			if (/*m_CurrentPoint.x < leftBoundary ||*/ m_CurrentPoint.x > rightBoundary)
			{
				m_HasExited = true; // ????????, ??? ??? ??????? ????
				m_Velocity.x = 0; // ?????????? ???
			}

			break;
		}
		
	case Entity::State::Calm:
		{
			break;
		}
	}
}

void Ballon::Draw() const  
{
	SetColor({ BallonColor });
	FillEllipse( m_CurrentPoint,  Radius, Radius);

}

Circlef Ballon::getGeometry() {
	return m_Geometry;
}

bool Ballon::HasExited() const
{
	return m_HasExited;
}