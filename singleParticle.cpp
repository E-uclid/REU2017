#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Particle.h"
#include "threevector.h"
#include "threematrix.h"

using namespace std;

vector< vector<double>> inData;

double lookupRadB(double r, double z) {
	int i = 0;
	double radB = 0.0;
	bool matchFound = false;
	if (r > 0.05 || r < 0.035 || z < 0 || z > 0.025) {
		radB = 0.0;
	}
	else {
		while (!matchFound && i < inData.size()) {
			if (fabs(z - inData.at(i).at(0)) <= 0.00025 && fabs(r - inData.at(i).at(1)) <= 0.00025) {
				radB = inData.at(i).at(3);
				matchFound = true;
			}
			else {
				i++;
			}
		}
	}
	if (!matchFound) {
		radB = 0.0;
	}
	return radB;
}

int main() {
	ifstream fin;
	fin.open("trimmedData.txt");
	while (!fin.eof()) {
		vector<double> tempI(4);
		for (int i = 0; i < 4; i++) {
			fin >> tempI.at(i);
		}
		inData.push_back(tempI);
	}
	inData.pop_back();

	ofstream fout;
	fout.open("outData.txt");

	double dt = 5e-12;
	int tSteps = 100000;

	double zMin = 0.0;
	double zMax = 0.025;
	double zStep = 0.0005;
	double zSteps = (zMax - zMin) / zStep;
	double rMin = 0.035;
	double rMax = 0.05;
	double rStep = 0.0005;
	double rSteps = (rMax - rMin) / rStep;

	//Make Grid
	/*vector<Particle> grid;

	for (int i = 0; i < rSteps + 1; i++) {
		for (int j = 0; j < zSteps + 1; j++) {
			Particle tempP = Particle(ThreeVec(rMin + i * rStep, 0.0, zMin + j * zStep ), ThreeVec(0.0, 1e5, 0.0));
			tempP.setQ(-1.602e-19);
			tempP.setM(9.109e-31);
			tempP.setE(ThreeVec(0.0, 0.0, 0.0));
			tempP.setB(ThreeVec(lookupRadB(tempP.getPos().getX(),tempP.getPos().getZ()), 0.0, 0.0));
			tempP.updateVel(-0.5 * dt);
			tempP.updatePos(dt);
			grid.push_back(tempP);
		}
	}*/

	//Just One
	Particle testP = Particle(ThreeVec((rMax - rMin) / 2, 0.0, (zMax - zMin) / 2), ThreeVec(0.0, 1e5, 0.0))

	/*Particle testP = grid.at(5);
	for (int i = 0; i < tSteps; i++) {
		// Dummy set E
		double radB = lookupRadB(testP.getPos().getX(), testP.getPos().getZ());
		testP.setB(ThreeVec(radB, 0.0, 0.0));
		if (radB == 0.0) {
			testP.setVel(ThreeVec());
		}
		else {
			testP.updateVel(dt);
		}
		testP.updatePos(dt);
		fout << testP.getPos().getX() << "\t" << testP.getPos().getY() << "\t" << testP.getPos().getZ() << "\t" << testP.getB().getX() << "\n";
	}*/

	testP.print();

	fout.close();
	system("pause");
}

