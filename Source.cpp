#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Cell.h"
#include "Particle.h"
#include "threevector.h"
#include "variables.h"

using namespace std;

double rtd() {
	return ((double)rand() / RAND_MAX);
}

double getCellVal(double r, double z, int i) {
	int zC = z / 0.0005;
	int rC = r / 0.0005;
	double val = 0.25 * vars::nodes.at(rC + 1).at(zC + 1).getVal(i) +
	0.25 * vars::nodes.at(rC + 1).at(zC).getVal(i) +
	0.25 * vars::nodes.at(rC).at(zC + 1).getVal(i) +
	0.25 * vars::nodes.at(rC).at(zC).getVal(i);
	return val;
}

int main() {
	// Control section

	double totalT = 1e-9;
	double dt = 1e-12;
	double tSteps = totalT / dt;

	// Open out stream

	ofstream fout;
	fout.open("output.txt");

	// Seed randoms

	srand(time(NULL));

	// Load data
	// z [m], r [m], e- density [m^-3], e- temp [eV], neutral density [m^-3],
	// Axial E [V/m], Radial E [V/m], Axial B [T], Radial B [T]

	int dims = 9;
	vector< vector<double>> dataIn;
	ifstream fin;
	fin.open("trimmedData.txt");
	while (!fin.eof()) {
		vector<double> tempI(dims);
		for (int i = 0; i < dims; i++) {
			fin >> tempI.at(i);
		}
		dataIn.push_back(tempI);
	}

	// Create cell matrix
	/*
	for (int i = 0; i < 30; i++) {
		vector<Cell> tempV;
		for (int j = 0; j < 50; j++) {
			vector<double> NW = dataIn.at((i + 1) * 51 + j);
			vector<double> NE = dataIn.at((i + 1) * 51 + (j + 1));
			vector<double> SW = dataIn.at(i * 51 + j);
			vector<double> SE = dataIn.at(i * 51 + (j + 1));
			Cell tempC = Cell(NE, NW, SW, SE);
			tempV.push_back(tempC);
		}
		vars::cells.push_back(tempV);
	}*/

	// Create node matrix

	for (int i = 0; i < 31; i++) {
		vector<Node> tempV;
		for (int j = 0; j < 51; j++) {
			tempV.push_back(Node(dataIn.at(i * 51 + j)));
		}
		vars::nodes.push_back(tempV);
	}

	// Create storage for particles

	vector<Particle> parts;

	// Test particle

	Particle testP = Particle(ThreeVec(0.0425, 0.0, 0.0), ThreeVec(0.0, 1e5, 0.0), -1.60218e-19, 9.10938e-31, 1.0);
	parts.push_back(testP);

	// Stepping process

	for (int i = 0; i < tSteps; i++) {
		// Move existing particles
			// Identify wall conditions
				// Do something else
		// Update cells based on particle changes
		// Scan through cells
			// Create particles appropriately
				// Push them back on parts
		
		for (int j = 0; j < parts.size(); j++) {
			parts.at(j).getPos().print();
			parts.at(j).getPos().print(fout);/*
			double axE = parts.at(j).getVal(5);
			double radE = parts.at(j).getVal(6);
			double axB = parts.at(j).getVal(7);
			double radB = parts.at(j).getVal(8);*/
			parts.at(j).updateVel(dt, ThreeVec(0.0, 0.0, 0.0), ThreeVec(0.0, 0.0, 0.1));
			parts.at(j).updatePos(dt);
			// Wall?
		}
		
	}

	testP.printV();

	fout.close();
	system("pause");
}