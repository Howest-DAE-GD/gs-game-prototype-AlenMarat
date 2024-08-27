#include "utils.h"
#include"Ballon.h"
#include <vector>
#include "pch.h"
#include "Game.h"
#include <iostream>
using namespace utils;

Ballon::Ballon(Game* game, Point2f start_point, float Radius, Color4f BC)
	:Entity(game, start_point), BallonColor{ BC }, Radius{ Radius }, m_HasExited{ false }

{
	blockKeys = false;
	m_Geometry = Circlef{ start_point, Radius };
	//m_PrevState = Entity::State::Dead;
	m_Velocity = Vector2f(150, 0);
	m_HasExited = false;
}
float Ballon::getR() {
	return Radius;
}

void Ballon::Update(float elapsedSec)
{
	if (!blockKeys) {
		switch (m_CurrentState)
		{
		case Entity::State::Moving:
		{
			m_CurrentPoint.x += m_Velocity.x * elapsedSec;
			float rightBoundary = m_pGame->GetViewPort().width - m_pGame->getTerrWidth() / 2;

			if (/*m_CurrentPoint.x < leftBoundary ||*/ m_CurrentPoint.x > rightBoundary)
			{
				m_HasExited = true; // ????????, ??? ??? ??????? ????
				SetState(Entity::State::Calm);// ?????????? ???
				//one ball escaped, launch another one
				m_pGame->goNextBallon();
				break;
			}

			if (m_CurrentPoint.y >= m_pGame->getEnemyTerritoryWidth() + Radius && m_CurrentPoint.y <= m_pGame->GetViewPort().height - m_pGame->getEnemyTerritoryWidth() - Radius) {
				m_CurrentPoint.y += m_Velocity.y * elapsedSec;
			}
			else
			{
				m_Velocity.y = -m_Velocity.y;
				m_CurrentPoint.y += m_Velocity.y * elapsedSec * 1.05;
			}



			m_Geometry.center.x = m_CurrentPoint.x;
			m_Geometry.center.y = m_CurrentPoint.y;
			break;
		}

		case Entity::State::Calm:
		{
			m_Velocity.x = 0;
			m_Velocity.y = 0;
			m_Geometry.center.x = m_CurrentPoint.x;
			m_Geometry.center.y = m_CurrentPoint.y;
			//std::cout << "Ballon is Calm. Velocity set to (0, 0)." << std::endl;
			break;
		}

		}
	}
}
void Ballon::setBlock(bool state) {
	blockKeys = state;
}

void Ballon::Draw() const
{
	if (!blockKeys) {
		SetColor({ BallonColor });
		if ((m_CurrentState != Entity::State::Dead))
		{
			FillEllipse(m_CurrentPoint, Radius, Radius);
		}

	}
}

Circlef Ballon::getGeometry() {
	return m_Geometry;
}

//bool Ballon::HasExited() const
//{
//	return m_HasExited;
//}

void Ballon::setVelocity(Vector2f V)
{
	m_Velocity = V;
}

Vector2f Ballon::getVelocity()
{
	return m_Velocity;
}

bool Ballon::HasExited()
{
	return m_HasExited;
}
