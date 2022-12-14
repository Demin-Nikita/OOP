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

int main()
{
	std::ifstream in;
	in.open("input.txt");
	
	int count = 0;
	rectangle_t frame{};
	int n = 0;
	std::string name;
	Shape* s;
	CompositeShape complex;
	Rectangle r;
	
	std::string type;

	Shape** mass = new Shape*;

	while (true) {
		in >> type;
		if (type == "COMPLEX") {
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
		if (type == "q") {
			break;
		}
	}

	std::cout << *(mass[0]) << '\n';
	std::cout << *(mass[1]) << '\n';
	std::cout << *(mass[2]) << '\n' << '\n';

	gfsort(mass, count);

	std::cout << *(mass[0]) << '\n';
	std::cout << *(mass[1]) << '\n';
	std::cout << *(mass[2]) << '\n';

	

	
	/*for (int i = 0; i < 3; i++) {
		std::cout << mass[i][0];
	}*/
	//std::cout << mass[0][0] << '\n';
	/*std::cout << mass[1][0] << '\n';
	std::cout << mass[2][0] << '\n';*/
	in.close();
	return 0;
}