#include <iomanip>
#include "Shape.h"
#include "Rectangle.h"
#include "Diamond.h"

std::ostream& operator<< (std::ostream& out, Shape& s) {
	float lbx = 0, lby = 0, rtx = 0, rty = 0;
	lbx = s.getFrameRect().pos.x - s.getFrameRect().width / 2;
	lby = s.getFrameRect().pos.y - s.getFrameRect().height / 2;
	rtx = s.getFrameRect().pos.x + s.getFrameRect().width / 2;
	rty = s.getFrameRect().pos.y + s.getFrameRect().height / 2;
	return (out << std::fixed << std::setprecision(1) << s.getName() << " " << s.getArea() << " lb: (" << lbx << "; " << lby << ") rt: (" << rtx << "; " << rty << ")");
}

bool Shape::operator< (Shape& right) {
	return (this->getArea() < right.getArea());
}