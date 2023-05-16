#pragma once
#include "pch.h"
#include "Curve.h"

namespace Main {
	class CURVES_API Helix : public Curve {
		double radius, pitch;
	public:
		Helix();
		Helix(double radius, double pitch);
		~Helix();

		void setRadius(double new_radius) override;

		void setPitch(double new_pitch);

		double getRadius() override;

		double getPitch();

		Point3D getPoint3D(double t) override;

		std::vector<Point3D> getFirstDerivative(double t) override;

		int getType() override;
	};
}