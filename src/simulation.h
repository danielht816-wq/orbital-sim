#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <unordered_map>
#include <fstream>
#include "Body.h"

using namespace std;

class Simulation {
private:
	unordered_map<string, Body> system;

	double G;
	double dt;
	int steps;
	string system_center;
	string outputFile;

	bool collisionDetected;

public:
	Simulation();

	void setSettings(double new_G, double new_dt, int new_steps, string new_center, string new_output_file);

	void addBody(string name, Body body);

	bool execute();

private:
	void resetAccelerations();
	void applyGravity();
	void updateVelocities();
	void updatePositions();
	void printBodies();
	bool checkCollisions(int step);
	void exportStep(ofstream& outFile, int step);

};


#endif