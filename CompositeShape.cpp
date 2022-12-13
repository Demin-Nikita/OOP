#include "CompositeShape.h"
#include <algorithm>

CompositeShape::CompositeShape(int len) {
	len_ = len;
	pos_.x = 0.0;
	pos_.y = 0.0;
}

void CompositeShape::addShape(Shape* s, int i) {
	Shape* s_copy;
	s_copy = s->clone();
	complex_[i] = s_copy;

	pos_.x = s->getFrameRect().pos.x;
	pos_.y = s->getFrameRect().pos.y;
}

float CompositeShape::getArea() {
	float s = 0;
	for (int i = 0; i < len_; i++) {
		s += complex_[i][0].getArea();
	}
	return s;
}

Shape* CompositeShape::clone() {
	Shape* s;
	CompositeShape comp(this->len_);
	comp.complex_ = this->complex_;
	comp.pos_ = this->pos_;
	s = &comp;
	return s;
}

std::string CompositeShape::getName() {
	return this->name_;
}

rectangle_t CompositeShape::getFrameRect() {
	float lbx = 1e10, lby = 1e10, rtx = -1e10, rty = -1e10;
	rectangle_t buff{};
	rectangle_t frame{};
	for (int i = 0; i < len_; i++) {
		buff = complex_[i][0].getFrameRect();
		
		float blbx = buff.pos.x - buff.width / 2;
		float blby = buff.pos.y - buff.height / 2;
		float brtx = buff.pos.x + buff.width / 2;
		float brty = buff.pos.y + buff.height / 2;

		blbx < lbx ? lbx = blbx : lbx;
		blby < lby ? lby = blby : lbx;
		brtx > rtx ? rtx = brtx : rtx;
		brty > rty ? rty = brty : rty;
	}
	frame.width = rtx - lbx;
	frame.height = rty - lby;
	frame.pos.x = lbx + frame.width / 2;
	frame.pos.y = lby + frame.height / 2;
	return frame;
}

void CompositeShape::move(float k) {
	for (int i = 0; i < len_; i++) {
		complex_[i][0].move(k);
	}
}

void CompositeShape::move(point_t& p) {
	float dx = 0, dy = 0;
	dx = p.x - pos_.x;
	dy = p.y - pos_.y;
	std::cout << pos_.x << " " << pos_.y << "\n";
	point_t tp{};

	for (int i = 0; i < len_; i++) {
		tp.x = complex_[i][0].getFrameRect().pos.x + dx;
		tp.y = complex_[i][0].getFrameRect().pos.y + dy;
		complex_[i][0].move(tp);
	}
}

void CompositeShape::scale(float k) {
	point_t tp{};

	for (int i = 0; i < len_; i++) {
		tp.x = complex_[i][0].getFrameRect().pos.x + (complex_[i][0].getFrameRect().pos.x - pos_.x) * k;
		tp.y = complex_[i][0].getFrameRect().pos.y + (complex_[i][0].getFrameRect().pos.y - pos_.y) * k;
		complex_[i][0].move(tp);
		complex_[i][0].scale(k);
	}
}