#include "Physics.h"
#include <cmath>

double distance(Body& a, Body& b) {
    double dx = a.getx() - b.getx();
    double dy = a.gety() - b.gety();

    return sqrt((dx * dx) + (dy * dy));
}

void createGravity(Body& a, Body& b, double gravityFactor) {
    double G = gravityFactor;

    double dx = b.getx() - a.getx();
    double dy = b.gety() - a.gety();

    double dxdy = distance(a, b);

    if (dxdy == 0) {
        return;
    }

    double directionx = dx / dxdy;
    double directiony = dy / dxdy;

    double acceleration = (G * b.getMass()) / (dxdy * dxdy);

    double ax = acceleration * directionx;
    double ay = acceleration * directiony;

    a.addAcceleration(ax, ay);
}

double kineticEnergy(Body& body) {
    double mass = body.getMass();
    double speed = body.getv();

    return 0.5 * mass * pow(speed, 2);
}

double potentialEnergy(Body& center, Body& target, double G) {
    double dist = distance(center, target);

    if (dist == 0) {
        return 0;
    }

    return (-1 * G * center.getMass() * target.getMass()) / dist;
}

bool haveCollided(Body& a, Body& b) {
    double trueDistance = distance(a, b);
    double combinedR = a.getRadius() + b.getRadius();

    return trueDistance <= combinedR;
}

void resolveElasticCollision(Body& a, Body& b) {

}