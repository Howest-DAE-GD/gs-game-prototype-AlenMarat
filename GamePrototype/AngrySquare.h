#pragma once
#pragma once
#pragma once
#include "Entity.h"
#include "Ballon.h"

class AngrySquare : public Entity
{
public:
    AngrySquare(Game* game, Point2f start_point, float size, Color4f color, float delay);

    void Update(float elapsedSec) override;
    void Draw() const override;
    bool IsHitting(Ballon* ball);
    void setBlock(bool state);
private:
    Rectf m_Geometry;
    Vector2f m_Velocity;
    float m_Size;
    Color4f m_Color;
    float m_ElapsedTime;
    float m_StartDelay;
    float MAXVelocity = 500;
    float MINVelocity = 200;
    bool blockKeys;
    float m_Frequency;
    float m_yflyRange;
};




