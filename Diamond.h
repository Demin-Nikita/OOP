#pragma once
#include "Shape.h"

class Diamond : public Shape
{
public:
	Diamond();
	Diamond(float px, float py, float xdiag, float ydiag);
	~Diamond();

	float getArea() override;
	rectangle_t getFrameRect();
	void move(float k);
	void move(point_t& p);
	void scale(float k);
	std::string getName();
	Shape* clone();
private:
	point_t pos_;
	float xdiag_, ydiag_;
	std::string name_ = "DIAMOND";
};