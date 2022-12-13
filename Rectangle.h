#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(float lbx, float lby, float rtx, float rty);
	~Rectangle();

	point_t getLB();
	point_t getRT();

	virtual float getArea() override;
	virtual rectangle_t getFrameRect();
	virtual void move(float k);
	virtual void move(point_t& p);
	virtual void scale(float k);
	virtual std::string getName();
	virtual Shape* clone();

private:
	point_t lb_, rt_;
	std::string name_ = "RECTANGLE";
};