

#pragma once
#include <utility>


struct Point{

public:
	Point():m_x(0.f), m_y(0.f), m_z(0.f){};
	Point(float x, float y, float z):m_x(x), m_y(y), m_z(z){};
	~Point(){};
	
public:	
	float m_x;
	float m_y;
	float m_z;
	
};


class Curve{

public:
	Curve():m_center(0.f, 0.f, 0.f){};
	Curve(float x, float y, float z = 0.f):m_center(x, y, z){};
	virtual ~Curve() = default;

	//Interface
	virtual Point getPointByAngle(float angleRads) const = 0;
	virtual Point getDerivativeByAngle(float angleRads) const = 0;
	virtual std::pair<float, float> getRadius() const = 0;

protected:
	Point m_center;
};



class Circle : public Curve{

public:
	Circle();
	Circle(float radius, float x, float y, float z = 0.f);
	~Circle() override = default;

	Point getPointByAngle(float angleRads) const override;
	Point getDerivativeByAngle(float angleRads) const override;
	std::pair<float, float> getRadius() const override;

private:
	float m_radius;

};


class Elipse : public Curve{

public:
	Elipse();
	Elipse(float radius_x, float radius_y, float x, float y, float z = 0.f);
	~Elipse() override = default;

	Point getPointByAngle(float angleRads) const override;
	Point getDerivativeByAngle(float angleRads) const override;
	std::pair<float, float> getRadius()const override;

private:
	float m_radius_x;
	float m_radius_y;
};


class Helix : public Curve{

public:
	Helix();
	Helix(float radius, float step_z, float x, float y, float z = 0.f);
	~Helix() override = default;

	Point getPointByAngle(float angleRads) const override;
	Point getDerivativeByAngle(float angleRads) const override;
	std::pair<float, float> getRadius()const override;

private:
	float m_radius;
	float m_step_z;
};





