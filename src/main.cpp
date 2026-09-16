#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <iterator>
#include "Body.h"
#include "physics.h"
#include "LoadFiles.h"
#include "simulation.h"

using namespace std;

//main
int main(int argc, char* argv[]) {


    string bodiesFile = "scenarios/earthsunmoon.txt";
    string settingsFile = "settings/earthsunmoon_settings.txt";
    string outputFile = "output/earthsunmoon_results.csv";

    if (argc >= 2) {
        bodiesFile = argv[1];
    }

    if (argc >= 3) {
        settingsFile = argv[2];
    }

    //gravity and time variables
    double G = 0.1;
    double dt = 0.01;
    int steps = 10000;
    string system_center = "Sun";

    getSettings(settingsFile, G, dt, steps, system_center, outputFile);
    if (argc >= 4) {
        outputFile = argv[3];
    }

    //additional(and optional) argument for user inputted steps
    if (argc >= 5) {
        steps = std::stoi(argv[4]);
    }

    cout << "Bodies file: " << bodiesFile << endl;
    cout << "Settings file: " << settingsFile << endl;
    cout << "Output file: " << outputFile << endl;
    cout << "G: " << G << endl;
    cout << "dt: " << dt << endl;
    cout << "steps: " << steps << endl;
    cout << "center: " << system_center << endl;

    unordered_map<string, Body> loadedBodies;

    getBodies(bodiesFile, loadedBodies);

    cout << "Loaded bodies:" << endl;

    for (auto& pair : loadedBodies) {
        cout << pair.first << endl;
    }

    Simulation sim;
    sim.setSettings(G, dt, steps, system_center, outputFile);

    for (auto& object : loadedBodies) {
        sim.addBody(object.first, object.second);
    }

    if (!sim.execute()) {
        return 1;
    }

    

    return 0;
}


//to run from cmd: "x64\Debug\solar system.exe" "scenarios\earthsunmoon.txt" "settings\earthsunmoon_settings.txt" "output\results.csv"