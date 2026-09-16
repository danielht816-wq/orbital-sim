#ifndef PHYSICS_H
#define PHYSICS_H

#include "Body.h"

double distance(Body& a, Body& b);

void createGravity(Body& a, Body& b, double gravityFactor);

double kineticEnergy(Body& body);

double potentialEnergy(Body& center, Body& target, double G);

bool haveCollided(Body& a, Body& b);

void resolveElasticCollision(Body& a, Body& b);

#endif