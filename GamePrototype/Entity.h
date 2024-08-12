#pragma once
#include "pch.h"
#include "structs.h"
#include <vector>

class Game;

class Entity
{
public:
    enum class State
    {
        Moving,
        Calm,
        Dead,
    };

    Entity(Game* game, const Point2f& start_point);
    virtual ~Entity() = default;

    virtual void Update(float elapsedSec) = 0;  
    virtual void Draw() const = 0;  

    void SetPosition(const Point2f& newPosition);  
    Point2f GetPosition() const;  

    void SetState(State newState);  
    State GetState() const; 

protected:
    Game* m_pGame; 
    Point2f m_CurrentPoint;  
    State m_CurrentState{ State::Calm }; 
    State m_PrevState{ State::Calm };  
    bool m_StateInitialized{ false };  
};

