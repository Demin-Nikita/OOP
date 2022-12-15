#pragma once
#include "Shape.h"

class CompositeShape : public Shape
{
public:
	CompositeShape();
	~CompositeShape();

	void addShape(Shape* s);
	float getArea();
	Shape* clone();
	rectangle_t getFrameRect();
	std::string getName();
	void move(float k);
	void move(point_t& p);
	void scale(float k);
private:
	Shape** complex_ = new Shape*;
	int len_;
	point_t pos_;
	std::string name_ = "COMPLEX";
};