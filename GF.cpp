#include <iostream>
#include <fstream>
#include "Basetypes.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Diamond.h"
#include "CompositeShape.h"

void gfsort(Shape** mass, int count);

void moveXY(Shape* shape, float dx, float dy);

void isotropicScale(Shape* shape, float posX, float posY, float k);

Rectangle* readRect(std::ifstream& in);

Diamond* readDiamond(std::ifstream& in);

void moveAll(Shape** mass, int count, std::ifstream& in);

void scaleAll(Shape** mass, int count, std::ifstream& in);

int main()
{
	std::cout << "Enter the path to the input file: ";
	std::string inputFile;
	std::cin >> inputFile;
	
	std::ifstream in;
	
	try {
		in.open(inputFile);
		if (!in) {
			throw std::runtime_error("no such file or directory");
		}
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	
	int count = 0;
	int n = 0;
	std::string name;
	
	CompositeShape complex;
	std::string type;

	Shape** mass = new Shape*[50];

	while (!in.eof()) {
		in >> type;
		if (type == "COMPLEX") {
			in >> n;
			for (int i = 0; i < n; i++) {
				in >> name;
				if (name == "RECTANGLE") {
					Shape* s = readRect(in);
					if (s != NULL) {
						complex.addShape(s);
					}
				}
				else if (name == "DIAMOND") {
					Shape* s = readDiamond(in);
					if (s != NULL) {
						complex.addShape(s);
					}
				}
				else {
					in.ignore(100, '\n');
				}
			}
			mass[count] = &complex;
			count++;
		}
		else if (type == "RECTANGLE") {
			Shape* s = readRect(in);
			if (s != NULL) {
				mass[count] = s->clone();
				count++;
			}
		}
		else if (type == "DIAMOND") {
			Shape* s = readDiamond(in);
			if (s != NULL) {
				mass[count] = s->clone();
				count++;
			}
		}	
		else if (type == "MOVE") {
			moveAll(mass, count, in);
		}
		else if (type == "SCALE") {
			scaleAll(mass, count, in);
		}
		else {
			in.ignore(100, '\n');
		}
	}

	gfsort(mass, count);
	
	std::cout << "SHAPES AFTER SORTING: \n";
	for (int i = 0; i < count; i++) {
		std::cout << *(mass[i]) << '\n';
	}
	
	delete[] mass;
	in.close();
	return 0;
}

Rectangle* readRect(std::ifstream& in) {
	float lbx = 0, lby = 0, rtx = 0, rty = 0;
	in >> lbx >> lby >> rtx >> rty;
	if (rtx <= lbx or rty <= lby) {
		std::cerr << "Errors in the description of figures! (RECTANGLE is not accepted) \n";
		return NULL;
	}
	Rectangle r(lbx, lby, rtx, rty);
	return &r;
}

Diamond* readDiamond(std::ifstream& in) {
	float posX = 0, posY = 0, xdiag = 0, ydiag = 0;
	in >> posX >> posY >> xdiag >> ydiag;
	if (xdiag <= 0 or ydiag <= 0) {
		std::cerr << "Errors in the description of figures! (DIAMOND is not accepted) \n";
		return NULL;
	}
	Diamond d(posX, posY, xdiag, ydiag);
	return &d;
}

void moveXY(Shape* shape, float dx, float dy) {
	point_t tp{};
	tp.x = shape->getFrameRect().pos.x + dx;
	tp.y = shape->getFrameRect().pos.y + dy;
	shape->move(tp);
}

void moveAll(Shape** mass, int count, std::ifstream& in) {
	float dx = 0, dy = 0;
	in >> dx >> dy;
	for (int i = 0; i < count; i++) {
		moveXY(mass[i], dx, dy);
	}
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

void scaleAll(Shape** mass, int count, std::ifstream& in) {
	float posX, posY, k;
	in >> posX >> posY >> k;
	for (int i = 0; i < count; i++) {
		isotropicScale(mass[i], posX, posY, k);
	}
}

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
