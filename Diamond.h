#pragma once
#include "Shape.h"

class Diamond : public Shape
{
public:
	Diamond();
	Diamond(float px, float py, float xdiag, float ydiag);
	~Diamond();

	point_t getPos();
	float getXdiag();
	float getYdiag();

	virtual float getArea() override;
	virtual rectangle_t getFrameRect();
	virtual void move(float k);
	virtual void move(point_t& p);
	virtual void scale(float k);
	virtual std::string getName();
	virtual Shape* clone();

private:
	point_t pos_;
	float xdiag_, ydiag_;
	std::string name_ = "DIAMOND";
};