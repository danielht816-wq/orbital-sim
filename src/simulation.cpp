#include "simulation.h"
#include "physics.h"

#include <iostream>
#include <iterator>

using namespace std;

Simulation::Simulation() {
	
	G = 0.1;
	dt = 0.01;
	steps = 100;
	system_center = "Sun";
	outputFile = "earthsunmoon_results.csv";
	collisionDetected = false;

}

void Simulation::setSettings(double new_G, double new_dt, int new_steps, string new_system_center, string new_outputFile) {
	G = new_G;
	dt = new_dt;
	steps = new_steps;
	system_center = new_system_center;
	outputFile = new_outputFile;
}

void Simulation::addBody(string name, Body body) {
	system.emplace(name, body);
}

void Simulation::resetAccelerations() {
	for (auto& object : system) {
		object.second.resetAcceleration();
	}
}

void Simulation::applyGravity() {
	for (auto& pairA : system) {
		for (auto& pairB : system) {
			if (pairA.first != pairB.first) {
				createGravity(pairA.second, pairB.second, G);
			}
		}
	}
}

void Simulation::updateVelocities() {
	for (auto& object : system) {
		if (!object.second.isFixed()) {
			object.second.changeVelocity(dt);
		}
	}
}

void Simulation::updatePositions() {
	for (auto& object : system) {
		if (!object.second.isFixed()) {
			object.second.changePosition(dt);
		}
	}
}

bool Simulation::checkCollisions(int step) {
	for (auto it1 = system.begin(); it1 != system.end(); ++it1) {
		for (auto it2 = next(it1); it2 != system.end(); ++it2) {

			if (haveCollided(it1->second, it2->second)) {
				cout << it1->second.getTitle()
					<< " collided with "
					<< it2->second.getTitle()
					<< " at step "
					<< step
					<< endl;
				resolveElasticCollision(it1->second, it2->second);
				return true;
			}
		}
	}
	//if no collision occurs
	return false;
}

//csv export func
void Simulation::exportStep(ofstream& outFile, int step) {
	for (auto& object : system) {

		double KE = kineticEnergy(object.second);
		double PE = 0;

		if (object.first != system_center) {
			PE = potentialEnergy(system.at(system_center), object.second, G);
		}

		double distancefromCenter = distance(object.second, system.at(system_center));

		outFile << step << ","
			<< object.second.getTitle() << ","
			<< object.second.getx() << ","
			<< object.second.gety() << ","
			<< object.second.getv() << ","
			<< distancefromCenter << ","
			<< KE << ","
			<< PE << ","
			<< KE + PE
			<< endl;
	}
}

void Simulation::printBodies() {
	for (auto& object : system) {
		object.second.printPosition();
	}
}

//system execution

bool Simulation::execute() {

	ofstream outFile(outputFile);
	if (!outFile) {
		cout << "Error: could not open output file: " << outputFile << endl;
		return false;
	}

	outFile << "step,body,x,y,speed,distancefromCenter,KE,PE,totalEnergy\n";

	//run system step by step
	for (int step = 1; step <= steps; step++) {
		cout << "Step #" << step << endl;

		resetAccelerations();

		applyGravity();

		updateVelocities();

		updatePositions();

		printBodies();

		collisionDetected = checkCollisions(step);

		exportStep(outFile, step);

		cout << endl;

		

	}
	outFile.close();
	return true;
}