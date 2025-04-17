

#include <iostream>
#include <cmath>

#include "Curve.h"


static constexpr float my_pi = static_cast<float>(4.f * atan(1.f));

//-----------------------------------------Circle-------------------------------------------
Circle::Circle() : m_radius(0.f){}

Circle::Circle(float radius, float x, float y, float z) :
	Curve(x, y, z)
{
	radius > 0? m_radius = radius : m_radius = 0.f;	
}

Point Circle::getPointByAngle(float angleRads) const {
	float x = m_center.m_x + m_radius * cos(angleRads);
	float y = m_center.m_y + m_radius * sin(angleRads);

	return Point(x, y, m_center.m_z);
}
	
Point Circle::getDerivativeByAngle(float angleRads) const {
	float dx = m_radius * (-sin(angleRads));
	float dy = m_radius * cos(angleRads);

	return Point(dx, dy, 0.f);
}

std::pair<float, float> Circle::getRadius() const {
	return std::make_pair(m_radius, 0.f);
}


//-----------------------------------------Elipse-------------------------------------------
Elipse::Elipse() : 
	m_radius_x(0.f), 
	m_radius_y(0.f)
{}

Elipse::Elipse(float radius_x, float radius_y, float x, float y, float z) : 
	Curve(x, y, z)
{
	radius_x > 0? m_radius_x = radius_x : m_radius_x = 0.f;	
	radius_y > 0? m_radius_y = radius_y : m_radius_y = 0.f;	
}

Point Elipse::getPointByAngle(float angleRads) const {
	float x = m_center.m_x + m_radius_x * cos(angleRads);
	float y = m_center.m_y + m_radius_y * sin(angleRads);

	return Point(x, y, m_center.m_z);
}
	
Point Elipse::getDerivativeByAngle(float angleRads) const {
	float dx = m_radius_x * (-sin(angleRads));
	float dy = m_radius_y * cos(angleRads);

	return Point(dx, dy, 0.f);
}

std::pair<float, float> Elipse::getRadius() const {
	return std::make_pair(m_radius_x, m_radius_y);
}

//-----------------------------------------Helix-------------------------------------------
Helix::Helix() : 
	m_radius(0.f)
{}

Helix::Helix(float radius, float step_z, float x, float y, float z) : 
	Curve(x, y, z),
	m_step_z(step_z)
{
	radius > 0? m_radius = radius : m_radius = 0.f;	
}

Point Helix::getPointByAngle(float angleRads) const {
	float x = m_center.m_x + m_radius * cos(angleRads);
	float y = m_center.m_y + m_radius * sin(angleRads);
	float z = m_center.m_z + (m_step_z * angleRads)/(2.f * my_pi);

	return Point(x, y, z);
}
	
Point Helix::getDerivativeByAngle(float angleRads) const {
	float dx = m_radius * (-sin(angleRads));
	float dy = m_radius * cos(angleRads);
	float dz = m_step_z/(2.f * my_pi);

	return Point(dx, dy, dz);
}

std::pair<float, float> Helix::getRadius() const {
	return std::make_pair(m_radius, 0.f);
}






