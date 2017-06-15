#pragma once
#include "threevector.h"
#include <vector>

class Node {
private:
	// Persisting indices 0 = z, 1 = r, 2 = e- density, 3 = e- temp, 4 = neutral density, 5 = ax E, 6 = rad E, 7 = ax B, 8 = rad B;
	std::vector<double> vals;

public:
	// Default Constructor
	Node() {
		vals = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	}

	// Constructor from input
	Node(std::vector<double> vals_) {
		vals = vals_;
	}

	// Accessor
	double getVal(int i) {
		return vals.at(i);
	}

	// Replace Modifier
	void setVal(double v, int i) {
		vals.at(i) = v;
	}

	// Addend Modifier
	void addVal(double v, int i) {
		vals.at(i) += v;
	}

	// Printer
	void print() {
		for (int i = 0; i < 9; i++) {
			std::cout << vals.at(i) << std::endl;
		}
	}
};