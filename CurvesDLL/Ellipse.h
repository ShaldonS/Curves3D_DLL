#pragma once
#include "Curve.h"

namespace Main {
	class CURVES_API Ellipse : public Curve {
		double radius_x, radius_y;
	public:
		Ellipse();
		Ellipse(double radius_x, double radius_y);
		~Ellipse();

		void setRadiusX(double new_radius_x);

		void setRadiusY(double new_radius_y);

		double getRadiusX();

		double getRadiusY();

		Point3D getPoint3D(double t) override;

		std::vector<Point3D> getFirstDerivative(double t) override;

		int getType() override;
	};
}
