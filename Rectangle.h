#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(float lbx, float lby, float rtx, float rty);
	~Rectangle();

	float getArea();
	rectangle_t getFrameRect();
	void move(float k);
	void move(point_t& p);
	void scale(float k);
	std::string getName();
	Shape* clone();
private:
	point_t lb_, rt_;
	std::string name_ = "RECTANGLE";
};