#pragma once
#include "Entity.h"
#include "Ballon.h"

class Square : public Entity
{
public:
    Square(Game* game, Point2f start_point, float size, Color4f color);

    void Update(float elapsedSec) override;
    void Draw() const override;
    bool IsHitting(Ballon* ball);
private:
    Rectf m_Geometry;
    float m_Velocity;
    float m_Size;
    Color4f m_Color;
};

