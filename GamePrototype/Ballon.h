#pragma once
#include "structs.h"
#include "Entity.h"
#include "Vector2f.h"
#include <iostream>


class Ballon : public Entity 
{
public:
	Ballon(Game* game, Point2f start_point,  float Radius, Color4f BC);
	
	void Update(float elapsedSec) override;
	void Draw() const override;
	Circlef getGeometry();
	
	float getR();
	bool HasExited() const;
	void setVelocity(Vector2f V);
	Vector2f getVelocity();
private:
	Circlef m_Geometry;
	Vector2f m_Velocity;
	Color4f BallonColor;
	float Radius;
	bool m_HasExited;

};
