#include "Square.h"
#include "utils.h"
#include <vector>
#include "pch.h"
#include <iostream>

#include "Game.h"
using namespace utils;

Square::Square(Game* game, Point2f start_point, float size, Color4f color,float delay)
    : Entity(game, start_point), m_Size(size), m_Color(color), m_StartDelay(delay), m_ElapsedTime(0.0f)
{
	m_Geometry = Rectf{ start_point.x,start_point.y,size,size };
    //m_PrevState = Entity::State::Calm;
	m_Velocity = Vector2f{ 0,-300 };

	//m_Velocity = Vector2f{ 0, -200.0f + static_cast<float>(rand() % 200) };
	//m_StartDelay = static_cast<float>(rand() % 2000) / 1000.0f;
}

void Square::Update(float elapsedSec)
{
	m_ElapsedTime += elapsedSec;

	
	if (m_ElapsedTime < m_StartDelay)
		return;
	
	switch (m_CurrentState)
	{
	case Entity::State::Moving:
		{
			if (((m_CurrentPoint.y <= 0) && (m_Velocity.y < 0)) || ((m_CurrentPoint.y >= m_pGame->GetViewPort().height) &&(m_Velocity.y>0)))
			{
				m_Velocity.y = -m_Velocity.y;
			}

			m_CurrentPoint.x += m_Velocity.x * elapsedSec;
			m_CurrentPoint.y += m_Velocity.y * elapsedSec;
			m_Geometry.left = m_CurrentPoint.x;
			m_Geometry.bottom = m_CurrentPoint.y;
			break;
		}

	
	}
}

bool Square::IsHitting(Ballon* ball) 
{
	//std::cout << "Square Y:" << m_Geometry.bottom << std::endl;
	//std::cout << "Ball X:" << ball->getGeometry().center.x << std::endl;
	if (IsOverlapping(m_Geometry, ball->getGeometry())) {
		return true;
	}
	else {
		return false;
	}
}

void Square::Draw() const
{
    SetColor(m_Color);
    FillRect(m_CurrentPoint.x - m_Size / 2, m_CurrentPoint.y - m_Size / 2, m_Size, m_Size);
}
