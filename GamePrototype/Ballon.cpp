#include "utils.h"
#include"Ballon.h"
#include <vector>
#include "pch.h"
using namespace utils;

Ballon::Ballon(Game* game, Point2f start_point,  float Radius, Color4f BC)
	:Entity(game, start_point), BallonColor{ BC }, Radius{Radius}
	
{
	m_Geometry = Circlef{ start_point, Radius };
	m_PrevState = Entity::State::Dead;
	m_Velocity = Vector2f(300,0);
}

void Ballon::Update(float elapsedSec)
{
	switch (m_CurrentState) 
	{
	case Entity::State::Moving:
		{
		m_CurrentPoint.x += m_Velocity.x * elapsedSec;
		m_CurrentPoint.y += m_Velocity.y * elapsedSec;
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