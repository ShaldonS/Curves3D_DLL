#pragma once
#include <vector>

enum { _Circle = 0, _Ellipse, _Helix };

class Point3D {
	double x, y, z;
public:
	Point3D() : x(0.0), y(0.0), z(0.0) {}
	Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
	~Point3D() {}

	void setX(double new_x) {
		x = new_x;
	}

	void setY(double new_y) {
		y = new_y;
	}

	void setZ(double new_z) {
		z = new_z;
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	double getZ() {
		return z;
	}
};

class Curve {
	Point3D point;
public:
	Curve() : point{} {}
	Curve(Point3D point) : point{ point } {}
	~Curve() {}

	void setFirstPoint(Point3D point) {
		point = point;
	}
	Point3D getFirstPoint() {
		return point;
	}

	virtual Point3D getPoint3D(double t) = 0;

	virtual std::vector<Point3D> getFirstDerivative(double t) = 0;

	virtual double getRadius() { return NULL; };
	virtual void setRadius(double new_radius) {};
	virtual int getType() = 0;
};

class Circle : public Curve {
	double radius;
public:
	Circle() : radius(0.0) { setFirstPoint(Point3D{}); }
	Circle(double radius) : radius(radius) { 
		if (radius < 0.0) throw "Radius less than 0.0. Exiting..."; setFirstPoint(Point3D{}); 
	}
	~Circle() {}

	void setRadius(double new_radius) override {
		if(new_radius >= 0.0)
			radius = new_radius;
	}

	double getRadius() override {
		return radius;
	}

	Point3D getPoint3D(double t) override {
		double x = getFirstPoint().getX() + radius * cos(t);
		double y = getFirstPoint().getY() + radius * sin(t);
		double z = getFirstPoint().getZ();
		return Point3D(x, y, z);
	}

	std::vector<Point3D> getFirstDerivative(double t) override {
		std::vector<Point3D> vec{ 2 };
		double x = -radius * sin(t);
		double y = radius * cos(t);
		double z = 0;
		Point3D pt_1{}, pt_2{ x, y, z };
		vec[0] = pt_1;
		vec[1] = pt_2;
		return vec;
	}
	int getType() override {
		return _Circle;
	}
};

class Ellipse : public Curve {
	double radius_x, radius_y;
public:
	Ellipse() : radius_x(0.0), radius_y(0.0) { setFirstPoint(Point3D{}); }
	Ellipse(double radius_x, double radius_y) : radius_x(radius_x), radius_y(radius_y) {
		if (radius_x < 0.0 || radius_y < 0.0) throw "Radius less than 0.0. Exiting...";
		setFirstPoint(Point3D{});
	}
	~Ellipse() {}

	void setRadiusX(double new_radius_x) {
		if (new_radius_x >= 0.0)
			radius_x = new_radius_x;
	}

	void setRadiusY(double new_radius_y) {
		if (new_radius_y >= 0.0)
			radius_y = new_radius_y;
	}

	double getRadiusX() {
		return radius_x;
	}

	double getRadiusY() {
		return radius_y;
	}

	Point3D getPoint3D(double t) override {
		double x = getFirstPoint().getX() + radius_x * cos(t);
		double y = getFirstPoint().getY() + radius_y * sin(t);
		double z = getFirstPoint().getZ();
		return Point3D(x, y, z);
	}

	std::vector<Point3D> getFirstDerivative(double t) override {
		std::vector<Point3D> vec{ 2 };
		double x = -radius_x * sin(t);
		double y = radius_y * cos(t);
		double z = 0;
		Point3D pt_1{}, pt_2{ x, y, z };
		vec[0] = pt_1;
		vec[1] = pt_2;
		return vec;
	}
	int getType() override {
		return _Ellipse;
	}
};

class Helix : public Curve {
	double radius, pitch;
public:
	Helix() : radius(0.0), pitch(0.0) { setFirstPoint(Point3D{}); }
	Helix(double radius, double pitch) : radius(radius), pitch(pitch) { 
		if (radius < 0.0) throw "Radius less than 0.0. Exiting...";
		setFirstPoint(Point3D{}); 
	}
	~Helix() {}

	void setRadius(double new_radius) override {
		if (new_radius >= 0.0)
			radius = new_radius;
	}

	void setPitch(double new_pitch) {
		pitch = new_pitch;
	}

	double getRadius() override {
		return radius;
	}

	double getPitch() {
		return pitch;
	}

	Point3D getPoint3D(double t) override {
		double x = getFirstPoint().getX() + radius * cos(t);
		double y = getFirstPoint().getY() + radius * sin(t);
		double z = getFirstPoint().getZ() + pitch * t / (2 * M_PI);
		return Point3D(x, y, z);
	}

	std::vector<Point3D> getFirstDerivative(double t) override {
		std::vector<Point3D> vec{ 2 };
		double x = -radius * sin(t);
		double y = radius * cos(t);
		double z = pitch;
		Point3D pt_1{}, pt_2{ x, y, z };
		vec[0] = pt_1;
		vec[1] = pt_2;
		return vec;
	}
	int getType() override {
		return _Helix;
	}
};