#include "pch.h"
#include "Circle.h"

namespace Main {
	Circle::Circle() : radius(0.0) { setFirstPoint(Point3D{}); }
	Circle::Circle(double radius) : radius(radius) {
		if (radius < 0.0) throw "Radius less than 0.0. Exiting..."; setFirstPoint(Point3D{});
	}
	Circle::~Circle() {}

	void Circle::setRadius(double new_radius) {
		if (new_radius >= 0.0)
			radius = new_radius;
	}

	double Circle::getRadius() {
		return radius;
	}

	Point3D Circle::getPoint3D(double t) {
		double x = getFirstPoint().getX() + radius * cos(t);
		double y = getFirstPoint().getY() + radius * sin(t);
		double z = getFirstPoint().getZ();
		return Point3D(x, y, z);
	}

	std::vector<Point3D> Circle::getFirstDerivative(double t) {
		std::vector<Point3D> vec{ 2 };
		double x = -radius * sin(t);
		double y = radius * cos(t);
		double z = 0;
		Point3D pt_1{}, pt_2{ x, y, z };
		vec[0] = pt_1;
		vec[1] = pt_2;
		return vec;
	}

	int Circle::getType() {
		return _Circle;
	}
}