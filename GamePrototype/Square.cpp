#include "Square.h"
#include "utils.h"
#include <vector>
#include "pch.h"
#include <iostream>
using namespace utils;

Square::Square(Game* game, Point2f start_point, float size, Color4f color)
    : Entity(game, start_point), m_Size(size), m_Color(color)
{
	m_Geometry = Rectf{ start_point.x,start_point.y,size,size };
    m_PrevState = Entity::State::Calm;
    m_Velocity = 300;  
}

void Square::Update(float elapsedSec)
{
	
	
	switch (m_CurrentState)
	{
	case Entity::State::Moving:
		{
			m_CurrentPoint.x -= m_Velocity * elapsedSec;
			m_Geometry.left = m_CurrentPoint.x;
			m_Geometry.bottom = m_CurrentPoint.y;
			break;
		}

	case Entity::State::Calm:
		{
			break;
		}
	}
}

bool Square::IsHitting(Ballon* ball) 
{
	std::cout << "Square X:" << m_Geometry.left << std::endl;
	std::cout << "Ball X:" << ball->getGeometry().center.x << std::endl;
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
