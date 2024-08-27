﻿#include "Entity.h"
#include "pch.h"
#include "Game.h"
#include <iostream>

Entity::Entity(Game* game, const Point2f& start_point)
    : m_pGame(game), m_CurrentPoint(start_point)
{
    // m_PrevState = Entity::State::Empty;
     //m_CurrentState = Entity::State::Calm;
    SetState(Entity::State::Calm);
}

void Entity::SetPosition(const Point2f& newPosition)
{
    m_CurrentPoint = newPosition;
}

Point2f Entity::GetPosition() const
{
    return m_CurrentPoint;
}

void Entity::SetState(State newState)
{
    // if (m_PrevState != newState)
     //{
        // m_PrevState = m_CurrentState;
    m_CurrentState = newState;
    // m_StateInitialized = false;  
 //}
}

Entity::State Entity::GetState() const
{
    return m_CurrentState;
}