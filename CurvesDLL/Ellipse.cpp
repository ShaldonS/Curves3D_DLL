#include "pch.h"
#include "Ellipse.h"

namespace Main {
	Ellipse::Ellipse() : radius_x(0.0), radius_y(0.0) { setFirstPoint(Point3D{}); }
	Ellipse::Ellipse(double radius_x, double radius_y) : radius_x(radius_x), radius_y(radius_y) {
		if (radius_x < 0.0 || radius_y < 0.0) throw "Radius less than 0.0. Exiting...";
		setFirstPoint(Point3D{});
	}
	Ellipse::~Ellipse() {}

	void Ellipse::setRadiusX(double new_radius_x) {
		if (new_radius_x >= 0.0)
			radius_x = new_radius_x;
	}

	void Ellipse::setRadiusY(double new_radius_y) {
		if (new_radius_y >= 0.0)
			radius_y = new_radius_y;
	}

	double Ellipse::getRadiusX() {
		return radius_x;
	}

	double Ellipse::getRadiusY() {
		return radius_y;
	}

	Point3D Ellipse::getPoint3D(double t) {
		double x = getFirstPoint().getX() + radius_x * cos(t);
		double y = getFirstPoint().getY() + radius_y * sin(t);
		double z = getFirstPoint().getZ();
		return Point3D(x, y, z);
	}

	std::vector<Point3D> Ellipse::getFirstDerivative(double t) {
		std::vector<Point3D> vec{ 2 };
		double x = -radius_x * sin(t);
		double y = radius_y * cos(t);
		double z = 0;
		Point3D pt_1{}, pt_2{ x, y, z };
		vec[0] = pt_1;
		vec[1] = pt_2;
		return vec;
	}

	int Ellipse::getType() {
		return _Ellipse;
	}
}