#ifndef INTEGRATIONS_1D_HPP
#define INTEGRATIONS_1D_HPP

#include "../general_definitions.hpp"

namespace Integration {
	class GaussLegendre_1D : Integration<1> {
	public:
		std::pair<std::vector<double>, std::vector<Point<1>>> GetRule(uint);
	private:
		std::pair<std::vector<double>, std::vector<Point<1>>> GPData(uint);
	};
}

#endif