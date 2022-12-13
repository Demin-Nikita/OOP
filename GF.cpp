#include <iostream>
#include "Basetypes.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Diamond.h"
#include "CompositeShape.h"

void gfsort(Shape** mass) {
	bool f = 1;
	while (f) {
		f = 0;
		for (int i = 0; i < 2; i++) {
			if (mass[i][0].getArea() > mass[i + 1][0].getArea()) {
				Shape* buff;
				buff = mass[i+1][0].clone();
				mass[i + 1] = mass[i][0].clone();
				mass[i] = buff;
				f = 1;
			}
		}
	}
}

int main()
{
	rectangle_t frame{};
	int n = 2;
	std::string name;
	Shape* s;
	CompositeShape complex(n);
	s = &complex;


	Shape* mass[3] = {};

	std::cout << "INPUT COMPLEX: \n";
	for (int i = 0; i < n; i++) {
		std::cin >> name;
		if (name == "RECTANGLE") {
			float lbx = 0, lby = 0, rtx = 0, rty = 0;
			std::cin >> lbx >> lby >> rtx >> rty;
			Rectangle r(lbx, lby, rtx, rty);
			complex.addShape(&r, i);
		}
		else if (name == "DIAMOND") {
			float posX = 0, posY = 0, xdiag = 0, ydiag = 0;
			std::cin >> posX >> posY >> xdiag >> ydiag;
			Diamond d(posX, posY, xdiag, ydiag);
			complex.addShape(&d, i);
		}
	}

	mass[0] = s;

	std::cout << "INPUT RECTANGLE: \n";
	float lbx = 0, lby = 0, rtx = 0, rty = 0;
	std::cin >> lbx >> lby >> rtx >> rty;
	Rectangle r(lbx, lby, rtx, rty);

	s = &r;
	mass[1] = s;

	std::cout << "INPUT DIAMOND: \n";
	float posX = 0, posY = 0, xdiag = 0, ydiag = 0;
	std::cin >> posX >> posY >> xdiag >> ydiag;
	Diamond d(posX, posY, xdiag, ydiag);

	s = &d;
	mass[2] = s;
	
	std::cout << mass[0][0] << '\n';

	gfsort(mass);

	

	/*for (int i = 0; i < 3; i++) {
		std::cout << mass[i][0];
	}
	std::cout << mass[0][0] << '\n';
	std::cout << mass[1][0] << '\n';
	std::cout << mass[2][0] << '\n';*/


	//При копировании составной фигуры напиши заполнение динамического массива. 
}