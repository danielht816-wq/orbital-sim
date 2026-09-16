#include "LoadFiles.h"
#include <iostream>
#include <fstream>

using namespace std;

void getBodies(string filename, unordered_map<string, Body>& system) {

    string title;
    double radius;
    double mass;
    double x, y;
    double vx, vy;
    double ax, ay;
    int fixedvalue;

    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "Error: invalid bodies file: " << filename << endl;
        return;
    }

    while (inputFile >> title >> radius >> mass >> x >> y >> vx >> vy >> ax >> ay >> fixedvalue) {

        bool fixed = fixedvalue == 1;

        Body newObject(title, radius, mass, x, y, vx, vy, ax, ay, fixed);

        system.emplace(title, newObject);
    }

    inputFile.close();
}

void getSettings(
    string filename,
    double& G,
    double& dt,
    int& steps,
    string& center,
    string& output
) {
    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "Error: invalid settings file: " << filename << endl;
        return;
    }

    string setting;

    while (inputFile >> setting) {

        if (setting == "G") {
            inputFile >> G;
        }
        else if (setting == "dt") {
            inputFile >> dt;
        }
        else if (setting == "steps") {
            inputFile >> steps;
        }
        else if (setting == "center") {
            inputFile >> center;
        }
        else if (setting == "output") {
            inputFile >> output;
        }
        else {
            cout << "Unknown setting: " << setting << endl;
        }
    }

    inputFile.close();
}