#pragma once
#include "threevector.h"
#include "variables.h"
#include <cmath>

class Particle
{
private:
	ThreeVec pos; // Position
	ThreeVec vel; // Velocity
	double q; // Charge
	double m; // Mass
	double weight; // Numerical Macroparticle Weight

public:
	// Default constructor, default values
	Particle() {
		pos = ThreeVec();
		vel = ThreeVec();
		q = 0.0;
		m = 0.0;
		weight = 1.0;
	}

	// Position/velocity constructor, default doubles
	Particle(ThreeVec pos_, ThreeVec vel_) {
		pos = pos_;
		vel = vel_;
		q = 0.0;
		m = 0.0;
		weight = 1.0;
	}

	// Full initialization constructor
	Particle(ThreeVec pos_, ThreeVec vel_, double q_, double m_, double w_) {
		pos = pos_;
		vel = vel_;
		q = q_;
		m = m_;
		weight = w_;
	}

	// Accessors and modifiers
	ThreeVec getPos() {
		return pos;
	}

	ThreeVec getVel() {
		return vel;
	}

	double getQ() {
		return q;
	}

	double getM() {
		return m;
	}

	double getW() {
		return weight;
	}

	void setPos(ThreeVec pos_) {
		pos = pos_;
	}

	void setVel(ThreeVec vel_) {
		vel = vel_;
	}

	void setQ(double q_) {
		q = q_;
	}

	void setM(double m_) {
		m = m_;
	}

	void setW(double w_) {
		weight = w_;
	}

	// Self - identify print method
	void print() {
		std::cout << "Particle at \n"
			<< pos.getR() << "\n"
			<< pos.getT() << "\n"
			<< pos.getZ() << "\n"
			<< "Traveling \n"
			<< vel.getR() << "\n"
			<< vel.getT() << "\n"
			<< vel.getZ() << "\n"
			<< "Charge \n"
			<< q << "\n"
			<< "Mass \n"
			<< m << std::endl;
	}

	// Update position based upon current velocity
	void updatePos(double dt_) {
		setPos(pos += vel * dt_);
	}

	// Update velocity based on fields (Boris push)
	void updateVel(double dt_, ThreeVec E_, ThreeVec B_) {
		// Cylindrical to Cartesian
		/*
		ThreeVec Ec = ThreeVec(E_.getR() * cos(E_.getT()), E_.getR() * sin(E_.getT()), E_.getZ());
		ThreeVec Bc = ThreeVec(B_.getR() * cos(B_.getT()), B_.getR() * sin(B_.getT()), B_.getZ());
		ThreeVec velc = ThreeVec(vel.getR() * cos(vel.getT()), vel.getR() * sin(vel.getT()), vel.getZ());
		*/
		ThreeVec t = B_ * (q / m) * dt_ * 0.5;
		ThreeVec u = (t * 2) / (1 + t.mag());
		ThreeVec vMinus = vel + E_ * (q / m) * dt_ * 0.5;
		ThreeVec vPrime = vMinus + (vMinus^t);
		ThreeVec vPlus = vMinus + (vPrime^u);
		ThreeVec outVel = vPlus + E_ * (q / m) * dt_ * 0.5;
		// Cartesian to Cylindricals
		/*
		ThreeVec outVel = ThreeVec(sqrt(pow(outVelc.getR(), 2.0) + pow(outVelc.getT(), 2.0)), - atan(outVelc.getT() / outVelc.getR()), outVelc.getZ());
		*/
		setVel(outVel);
	}

	// Locate current cell
	std::vector<int> locate() {
		int zC = pos.getZ() / 0.0005;
		int rC = (pos.getR() - 0.035) / 0.0005;
		return std::vector<int> {rC, zC};
	}

	// Retrieve i^th data value
	double getVal(int i) {
		std::vector<int> loc = locate();
		double r = pos.getR();
		double z = pos.getZ();
		double rRatio = (r - vars::nodes.at(loc.at(0)).at(loc.at(1) + 1).getVal(1)) / 0.0005;
		double zRatio = (z - vars::nodes.at(loc.at(0) + 1).at(loc.at(1)).getVal(0)) / 0.0005;
		double val = rRatio * zRatio * vars::nodes.at(loc.at(0) + 1).at(loc.at(1) + 1).getVal(i) +
			rRatio * (1 - zRatio) * vars::nodes.at(loc.at(0) + 1).at(loc.at(1)).getVal(i) +
			(1 - rRatio) * zRatio * vars::nodes.at(loc.at(0)).at(loc.at(1) + 1).getVal(i) +
			(1 - rRatio) * (1 - zRatio) * vars::nodes.at(loc.at(0)).at(loc.at(1)).getVal(i);
		return val;
	}

	// Location value printer
	void printV() {
		for (int i = 0; i < 9; i++) {
			std::cout << getVal(i) << std::endl;
		}
	}
};