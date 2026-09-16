#ifndef BODY_H
#define BODY_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

class Body {
public:
    Body(string s, double r, double m,
        double initial_x, double initial_y,
        double initial_vx, double initial_vy,
        double initial_ax, double initial_ay,
        bool isFixed);

    Body();

    void changePosition(double dt);
    void changeVelocity(double dt);

    void setVelocity(double new_vx, double new_vy);

    void setAcceleration(double new_ax, double new_ay);
    void resetAcceleration();
    void addAcceleration(double add_ax, double add_ay);

    void printPosition();

    string getTitle();
    double getx();
    double gety();
    double getv();
    double getvx();
    double getvy();
    double getMass();
    double getRadius();
    bool isFixed();

    vector<pair<double, double>> getTrail();

private:
    string title;
    double radius;
    double mass;
    double x, y;
    bool fixed;

    double vx, vy;
    double ax, ay;

    vector<pair<double, double>> trail;
};

#endif