#include "Diamond.h"

Diamond::Diamond() { pos_.x = 0.0; pos_.y = 0.0; xdiag_ = 0.0, ydiag_ = 0.0; }
Diamond::Diamond(float px, float py, float xdiag, float ydiag) { pos_.x = px; pos_.y = py; xdiag_ = xdiag; ydiag_ = ydiag; }
Diamond::~Diamond() = default;

point_t Diamond::getPos() {
	return this->pos_;
}

float Diamond::getXdiag() {
	return this->xdiag_;
}

float Diamond::getYdiag() {
	return this->ydiag_;
}

float Diamond::getArea() {
	return (this->xdiag_ * this->ydiag_) * 0.5;
}

rectangle_t Diamond::getFrameRect() {
	rectangle_t frame{};
	frame.height = this->ydiag_;
	frame.width = this->xdiag_;
	frame.pos.x = this->pos_.x;
	frame.pos.y = this->pos_.y;

	return frame;
}

void Diamond::move(float k) {
	this->pos_.x += k;
	this->pos_.y += k;
}

void Diamond::move(point_t& p) {
	this->pos_.x = p.x;
	this->pos_.y = p.y;
}

void Diamond::scale(float k) {
	this->xdiag_ *= k;
	this->ydiag_ *= k;
}

std::string Diamond::getName() {
	return this->name_;
}

Shape* Diamond::clone() {
	Shape* s;
	Diamond *d = new Diamond;
	d->pos_ = this->pos_;
	d->xdiag_ = this->xdiag_;
	d->ydiag_ = this->ydiag_;
	s = d;
	return s;
}
