#pragma once
#include "threevector.h"
#include <vector>

class Cell {
private:
	// Persisting indices 0 = z, 1 = r, 2 = e- density, 3 = e- temp, 4 = neutral density, 5 = ax E, 6 = rad E, 7 = ax B, 8 = rad B;
	// NE = +Z+R, NW = -Z+R, SW = -Z-R, SE = +Z-R
	std::vector<double> NE;
	std::vector<double> NW;
	std::vector<double> SW;
	std::vector<double> SE;

	// Dimensions of cell
	double deltR;
	double deltZ;

	// ?
	double rate;
public:
	// Default constructor
	Cell() {
		NE = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		NW = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		SW = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		SE = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		deltR = 0.0;
		deltZ = 0.0;
		rate = 0.0;
	}

	// Constructor from input
	Cell(std::vector<double> NE_, std::vector<double> NW_, std::vector<double> SW_, std::vector<double> SE_) {
		NE = NE_;
		NW = NW_;
		SW = SW_;
		SE = SE_;
		deltR = NE.at(1) - SE.at(1);
		deltZ = NE.at(0) - NW.at(0);
		rate = 0.5;
	}

	// Accessor for individual value
	double getVal(double r, double z, int i) {
		double rRatio = (r - SE.at(1)) / deltR;
		double zRatio = (z - NW.at(0)) / deltZ;
		double val = rRatio * zRatio * NE.at(i) + rRatio * (1 - zRatio) * NW.at(i) + (1 - rRatio) * zRatio * SE.at(i) + (1 - rRatio) * (1 - zRatio) * SW.at(i);
		return val;
	}

	// Modifier for individual value
	void setVal() {
		// Update the particular value or distribute over corners?
	}

	// Printer
	void print() {
		// Cycle CCW one var at a time
		for (int i = 0; i < 9; i++) {
			std::cout << NE.at(i) << std::endl << NW.at(i) << std::endl << SW.at(i) << std::endl << SE.at(i) << std::endl;
		}
	}
};