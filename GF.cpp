#include <iostream>
#include <fstream>
#include "Basetypes.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Diamond.h"
#include "CompositeShape.h"

void gfsort(Shape** mass, int count) {
	bool f = 1;
	Shape* buff;
	while (f) {
		f = 0;
		for (int i = 0; i < count - 1; i++) {
			if (*(mass[i + 1]) < *(mass[i])) {
				buff = &(*mass[i + 1]);
				mass[i + 1] = &(*mass[i]);
				mass[i] = &(*buff);
				f = 1;
			}
		}
	}
}

void moveXY(Shape* shape, float dx, float dy) {
	point_t tp{};
	tp.x = shape->getFrameRect().pos.x + dx;
	tp.y = shape->getFrameRect().pos.y + dy;
	shape->move(tp);
}

void isotropicScale(Shape* shape, float posX, float posY, float k) {
	point_t a1{};
	a1.x = shape->getFrameRect().pos.x - shape->getFrameRect().width / 2;
	a1.y = shape->getFrameRect().pos.y - shape->getFrameRect().height / 2;
	point_t isotropicCenter{};
	isotropicCenter.x = posX;
	isotropicCenter.y = posY;
	shape->move(isotropicCenter);
	point_t a2{};
	a2.x = shape->getFrameRect().pos.x - shape->getFrameRect().width / 2;
	a2.y = shape->getFrameRect().pos.y - shape->getFrameRect().height / 2;
	float dx = a1.x - a2.x;
	float dy = a1.y - a2.y;
	shape->scale(k);
	dx *= k;
	dy *= k;
	point_t tp{};
	tp.x = posX + dx;
	tp.y = posY + dy;
	shape->move(tp);
}

int main()
{
	std::ifstream in;
	in.open("input.txt");
	
	int count = 0;
	std::string type;

	Shape** mass = new Shape*;

	while (in) {
		in >> type;
		if (type == "COMPLEX") {
			CompositeShape complex;
			std::string name;
			int n = 0;
			in >> n;
			for (int i = 0; i < n; i++) {
				in >> name;
				if (name == "RECTANGLE") {
					float lbx = 0, lby = 0, rtx = 0, rty = 0;
					in >> lbx >> lby >> rtx >> rty;
					Rectangle r(lbx, lby, rtx, rty);
					complex.addShape(&r);
				}
				else if (name == "DIAMOND") {
					float posX = 0, posY = 0, xdiag = 0, ydiag = 0;
					in >> posX >> posY >> xdiag >> ydiag;
					Diamond d(posX, posY, xdiag, ydiag);
					complex.addShape(&d);
				}
			}
			mass[count] = &complex;
			count++;
		}
		if (type == "RECTANGLE") {
			float lbx = 0, lby = 0, rtx = 0, rty = 0;
			in >> lbx >> lby >> rtx >> rty;
			Rectangle r(lbx, lby, rtx, rty);
			mass[count] = r.clone();
			count++;
		}
		if (type == "DIAMOND") {
			float posX = 0, posY = 0, xdiag = 0, ydiag = 0;
			in >> posX >> posY >> xdiag >> ydiag;
			Diamond d(posX, posY, xdiag, ydiag);
			mass[count] = d.clone();
			count++;
		}
		if (type == "MOVE") {
			float dx = 0, dy = 0;
			in >> dx >> dy;
			for (int i = 0; i < count; i++) {
				moveXY(mass[i], dx, dy);
			}
		}
		if (type == "SCALE") {
			float posX, posY, k;
			in >> posX >> posY >> k;
			for (int i = 0; i < count; i++) {
				isotropicScale(mass[i], posX, posY, k);
			}
		}
	}

	gfsort(mass, count);
	
	for (int i = 0; i < count; i++) {
		std::cout << *(mass[i]) << '\n';
	}
	
	in.close();
	return 0;
}