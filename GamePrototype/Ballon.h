#pragma once
#include "structs.h"
#include "Entity.h"

class Ballon : public Entity 
{
public:
	Ballon(Game* game, Point2f start_point,  float Radius, Color4f BC);
	
	void Update(float elapsedSec) override;
	void Draw() const override;

private:
	float m_Velocity;
	Color4f BallonColor;
	float Radius;
};
