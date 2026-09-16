#include "Body.h"
#include <iostream>
#include <cmath>

using namespace std;

Body::Body(string s, double r, double m,
    double initial_x, double initial_y,
    double initial_vx, double initial_vy,
    double initial_ax, double initial_ay,
    bool isFixed) {
    title = s;
    radius = r;
    mass = m;
    x = initial_x;
    y = initial_y;
    vx = initial_vx;
    vy = initial_vy;
    ax = initial_ax;
    ay = initial_ay;
    fixed = isFixed;
}

Body::Body() {
    title = "";
    radius = 0;
    mass = 0;
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
    fixed = false;
}

void Body::changePosition(double dt) {
    x = x + (vx * dt);
    y = y + (vy * dt);

    trail.push_back({ x, y });
}

void Body::changeVelocity(double dt) {
    vx = vx + (ax * dt);
    vy = vy + (ay * dt);
}

void Body::setVelocity(double new_vx, double new_vy) {

}

void Body::setAcceleration(double new_ax, double new_ay) {
    ax = new_ax;
    ay = new_ay;
}

void Body::resetAcceleration() {
    ax = 0;
    ay = 0;
}

void Body::addAcceleration(double add_ax, double add_ay) {
    ax += add_ax;
    ay += add_ay;
}

void Body::printPosition() {
    cout << title << " current position: " << x << ", " << y << endl;
}

//getters
string Body::getTitle() {
    return title;
}

double Body::getx() {
    return x;
}

double Body::gety() {
    return y;
}

double Body::getv() {
    return sqrt(vx * vx + vy * vy);
}

double Body::getvx() {
    return vx;
}

double Body::getvy() {
    return vy;
}

double Body::getMass() {
    return mass;
}

double Body::getRadius() {
    return radius;
}

bool Body::isFixed() {
    return fixed;
}

vector<pair<double, double>> Body::getTrail() {
    return trail;
}