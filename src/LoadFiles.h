#ifndef LOADFILES_H
#define LOADFILES_H

#include <string>
#include <unordered_map>
#include "Body.h"

using namespace std;

void getBodies(string filename, unordered_map<string, Body>& system);

void getSettings(
    string filename,
    double& G,
    double& dt,
    int& steps,
    string& center,
    string& output
);

#endif