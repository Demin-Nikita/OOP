#pragma once
#include "Shape.h"

class CompositeShape : public Shape
{
public:
	CompositeShape();
	~CompositeShape();
	void addShape(Shape* s);

	virtual float getArea();
	virtual Shape* clone();
	virtual rectangle_t getFrameRect();
	virtual std::string getName();
	virtual void move(float k);
	virtual void move(point_t& p);
	//----------------------NEED TEST
	virtual void scale(float k);
	//----------------------END
private:
	Shape** complex_ = new Shape*;
	int len_;
	point_t pos_;
	std::string name_ = "COMPLEX";
};