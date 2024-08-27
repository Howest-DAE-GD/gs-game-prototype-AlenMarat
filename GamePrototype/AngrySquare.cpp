#include "AngrySquare.h"
#include "AngrySquare.h"
#include "AngrySquare.h"
#include "utils.h"
#include <vector>
#include "pch.h"
#include <iostream>

#include "Game.h"
using namespace utils;

AngrySquare::AngrySquare(Game* game, Point2f start_point, float size, Color4f color, float delay)
	: Entity(game, start_point), m_Size(size), m_Color(color), m_StartDelay(delay), m_ElapsedTime(0.0f)
{
	m_yflyRange = 5;
	m_Frequency = 0.2;
	blockKeys = false;
	m_Geometry = Rectf{ start_point.x,start_point.y,size,size };
	//m_PrevState = Entity::State::Calm;
	//srand(time(0));

	m_Velocity = Vector2f{ 0,-1 * rand() / RAND_MAX * (MAXVelocity - MINVelocity) + MINVelocity };

	//m_Velocity = Vector2f{ 0, -200.0f + static_cast<float>(rand() % 200) };
	//m_StartDelay = static_cast<float>(rand() % 2000) / 1000.0f;
}

void AngrySquare::Update(float elapsedSec)
{
	m_ElapsedTime += elapsedSec;


	if (m_ElapsedTime < m_StartDelay)
		return;

	if (!blockKeys)
	{
		switch (m_CurrentState)
		{
		case Entity::State::Moving:
		{
			if (((m_CurrentPoint.y <= 0) && (m_Velocity.y < 0)) || ((m_CurrentPoint.y >= m_pGame->GetViewPort().height) && (m_Velocity.y > 0)))
			{
				m_Velocity.y = -m_Velocity.y;
			}
			float t = m_pGame->getAbsoluteTime();
			float w = 1 / m_Frequency;
			m_CurrentPoint.x += m_yflyRange * sin(w * t);
			//m_CurrentPoint.x += sin(W*  elapsedSec);
			m_CurrentPoint.y += m_Velocity.y * elapsedSec;
			m_Geometry.left = m_CurrentPoint.x;
			m_Geometry.bottom = m_CurrentPoint.y;
			break;
		}


		}
	}

}

bool AngrySquare::IsHitting(Ballon* ball)
{
	//std::cout << "AngrySquare Y:" << m_Geometry.bottom << std::endl;
	//std::cout << "Ball X:" << ball->getGeometry().center.x << std::endl;
	if (IsOverlapping(m_Geometry, ball->getGeometry())) {
		return true;
	}
	else {
		return false;
	}
}

void AngrySquare::Draw() const
{
	if (!blockKeys)
	{
		SetColor(m_Color);
		FillRect(m_CurrentPoint.x - m_Size / 2, m_CurrentPoint.y - m_Size / 2, m_Size, m_Size);
	}

}

void AngrySquare::setBlock(bool state) {
	blockKeys = state;
}
