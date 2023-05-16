#pragma once
#include "Curve.h"

namespace Main {
	class CURVES_API Circle : public Curve {
		double radius;
	public:
		Circle();
		Circle(double radius);
		~Circle();

		void setRadius(double new_radius) override;

		double getRadius() override;

		Point3D getPoint3D(double t) override;

		std::vector<Point3D> getFirstDerivative(double t) override;

		int getType() override;
	};
}