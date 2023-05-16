#pragma once
#define _USE_MATH_DEFINES

#ifdef CURVESDLL_EXPORTS
#define CURVES_API __declspec(dllexport)
#else
#define CURVES_API __declspec(dllimport)
#endif // CURVES2DLL_EXPORTS

#include <vector>

enum { _Circle = 0, _Ellipse, _Helix };

namespace Main {
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
}