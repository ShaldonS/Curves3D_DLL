#define _USE_MATH_DEFINES

#include <omp.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

#pragma comment(lib,"CurvesDLL.lib")

#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
//#include "Curves.h"

using namespace Main;

int main(int argc, char** argv) {
	srand(time(NULL));

	// 2
	std::cout << "\n<<2>>\n";
	std::vector<std::shared_ptr<Curve>> curves;
	double rand_double(0.0), t(0.0), radius(0.0), radius_x(0.0), radius_y(0.0), h_radius(0.0), h_pitch(0.0);
	for (size_t i(0); i < 100; ++i) {
		rand_double = 0.0 + (double)rand() / RAND_MAX * (1'000'000.0);
		if (i < 33) {
			radius = rand_double;
			try {
				std::shared_ptr<Curve> circle = std::make_shared<Circle>(radius);
				curves.push_back(std::move(circle));
			}
			catch (const char* error_message) {
				std::cout << error_message << "\n";
				return 0;
			}
		}
		else if (i < 66) {
			radius_x = rand_double;
			radius_y = 0.0 + (double)rand() / RAND_MAX * (1'000'000.0);
			try {
				std::shared_ptr<Curve> ellipse = std::make_shared<Main::Ellipse>(radius_x, radius_y);
				curves.push_back(std::move(ellipse));
			}
			catch (const char* error_message) {
				std::cout << error_message << "\n";
				return 0;
			}
		}
		else {
			h_radius = rand_double;
			h_pitch = 0.0 + (double)rand() / RAND_MAX * (1'000'000.0);
			try {
				std::shared_ptr<Curve> helix = std::make_shared<Helix>(h_radius, h_pitch);
				curves.push_back(std::move(helix));
			}
			catch (const char* error_message) {
				std::cout << error_message << "\n";
				return 0;
			}
		}
	}
	
	// 3
	std::cout << "\n<<3>>\n";
	t = M_PI / 4;
	for (size_t i(0); i < curves.size(); ++i) {
		std::cout << "Point: (" << curves[i]->getPoint3D(t).getX() <<
			", " << curves[i]->getPoint3D(t).getY() <<
			", " << curves[i]->getPoint3D(t).getZ() << ")\n";
		Point3D pt_1{ curves[i]->getFirstDerivative(t)[0] }, pt_2{ curves[i]->getFirstDerivative(t)[1] };
		std::cout << "First derivative: (" <<
			pt_2.getX() - pt_1.getX() << ", " <<
			pt_2.getY() - pt_1.getY() << ", " <<
			pt_2.getZ() - pt_1.getZ() << ")\n";
	}
	
	// 4
	std::cout << "\n<<4>>\n";
	std::vector<std::shared_ptr<Curve>> curves_2;
	std::copy_if(curves.begin(), curves.end(),
		std::back_inserter(curves_2),
		[](auto&& c) {
		return c->getType() == _Circle;
	});
	
	std::cout << "After copy: \n";
	std::cout << curves[0]->getRadius() << " VS ";
	std::cout << curves_2[0]->getRadius() << " \n";
	std::cout << "After setting radius of Circle in first vector to 1.1: \n";
	curves[0]->setRadius(1.1);
	std::cout << curves[0]->getRadius() << " VS ";
	std::cout << curves_2[0]->getRadius() << " \n";
	
	// 5
	std::cout << "\n<<5>>\n";
	std::sort(curves_2.begin(), curves_2.end(),
		[](auto&& c1, auto&& c2) {
		return (double)c1->getRadius() < (double)c2->getRadius();
	});

	for (auto&& c : curves_2) {
		std::cout << c->getRadius() << "\n";
	}

	// 6
	std::cout << "\n<<6>>\n";
	double _sum(0.0);
	//for (auto&& c : curves_2) {
	for(auto c = curves_2.begin(); c != curves_2.end(); ++c) {
		_sum += (double)c->get()->getRadius();
	}
	std::cout << std::fixed << _sum << "\n";

	/*try {
		std::shared_ptr<Curve> circle = std::make_shared<Circle>(-1.0);
	}
	catch (const char* error_message) {
		std::cout << error_message << "\n";
		return 0;
	}*/
	
	// 8
	std::cout << "\n<<8>>\n";
	double sum(0.0);
	
	// filling with more elements
	for (size_t i(0); i < 1'000'000.0; ++i) {
		radius = 0.0 + (double)rand() / RAND_MAX * (1'000'000.0);
		try {
			std::shared_ptr<Curve> circle = std::make_shared<Circle>(radius);
			curves_2.push_back(std::move(circle));
		}
		catch (const char* error_message) {
			std::cout << error_message << "\n";
			return 0;
		}
	}
	// sorting again
	std::sort(curves_2.begin(), curves_2.end(),
		[](auto&& c1, auto&& c2) {
		return (double)c1->getRadius() < (double)c2->getRadius();
	});

	double start = omp_get_wtime();

	for (auto&& c : curves_2) {
		sum += (double)c->getRadius();
	}
	double end = omp_get_wtime();
	std::cout << std::fixed << sum << " | ";
	std::cout << "Single time: \t" << (double)(end - start) << "\n";

	sum = 0.0;

	start = omp_get_wtime();
#pragma omp parallel for reduction(+:sum)
	for (int i(0); i < curves_2.size(); ++i) {
		sum += (double)curves_2[i]->getRadius();
		//auto c = curves_2.begin() + i;
		//sum += (double)c->get()->getRadius();
	}
	end = omp_get_wtime();

	std::cout << std::fixed << sum << " | ";
	std::cout << "Parallel time: \t" << (double)(end - start) << "\n";
	
	return 0;
}