#include "Rectangle.h"

Rectangle::Rectangle() { lb_.x = 0.0; lb_.y = 0.0; rt_.x = 0.0; rt_.y = 0.0; }
Rectangle::Rectangle(float lbx, float lby, float rtx, float rty) {
	lb_.x = lbx; lb_.y = lby;
	rt_.x = rtx; rt_.y = rty;
}
Rectangle::~Rectangle() = default;

float Rectangle::getArea() {
	return (rt_.x - lb_.x) * (rt_.y - lb_.y);
}

rectangle_t Rectangle::getFrameRect() {
	rectangle_t FrameRect{};
	point_t pos{};
	FrameRect.width = rt_.x - lb_.x;
	FrameRect.height = rt_.y - lb_.y;
	pos.x = (rt_.x + lb_.x) / 2;
	pos.y = (rt_.y + lb_.y) / 2;
	FrameRect.pos = pos;
	
	return FrameRect;
}

void Rectangle::move(float k) {
	rt_.x += k; rt_.y += k;
	lb_.x += k; lb_.y += k;
}

void Rectangle::move(point_t& p) {
	float dx = (rt_.x - lb_.x) / 2;
	float dy = (rt_.y - lb_.y) / 2;

	rt_.x = p.x + dx; rt_.y = p.y + dy;
	lb_.x = p.x - dx; lb_.y = p.y - dy;
}

void Rectangle::scale(float k) {
	rectangle_t frame = getFrameRect();
	rt_.x = frame.pos.x + frame.width / 2 * k;
	rt_.y = frame.pos.y + frame.height / 2 * k;
	lb_.x = frame.pos.x - frame.width / 2 * k;
	lb_.y = frame.pos.y - frame.height / 2 * k;
}

std::string Rectangle::getName() {
	return this->name_;
}

Shape* Rectangle::clone() {
	Shape* s;
	Rectangle *r = new Rectangle;
	r->lb_ = this->lb_;
	r->rt_ = this->rt_;
	s = r;
	return s;
}