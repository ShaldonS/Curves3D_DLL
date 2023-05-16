#include "pch.h"
#include "Helix.h"

namespace Main {
	Helix::Helix() : radius(0.0), pitch(0.0) { setFirstPoint(Point3D{}); }
	Helix::Helix(double radius, double pitch) : radius(radius), pitch(pitch) {
		if (radius < 0.0) throw "Radius less than 0.0. Exiting...";
		setFirstPoint(Point3D{});
	}
	Helix::~Helix() {}

	void Helix::setRadius(double new_radius) {
		if (new_radius >= 0.0)
			radius = new_radius;
	}

	void Helix::setPitch(double new_pitch) {
		pitch = new_pitch;
	}

	double Helix::getRadius() {
		return radius;
	}

	double Helix::getPitch() {
		return pitch;
	}

	Point3D Helix::getPoint3D(double t) {
		double x = getFirstPoint().getX() + radius * cos(t);
		double y = getFirstPoint().getY() + radius * sin(t);
		double z = getFirstPoint().getZ() + pitch * t / (2 * M_PI);
		return Point3D(x, y, z);
	}

	std::vector<Point3D> Helix::getFirstDerivative(double t) {
		std::vector<Point3D> vec{ 2 };
		double x = -radius * sin(t);
		double y = radius * cos(t);
		double z = pitch;
		Point3D pt_1{}, pt_2{ x, y, z };
		vec[0] = pt_1;
		vec[1] = pt_2;
		return vec;
	}
	int Helix::getType() {
		return _Helix;
	}
}