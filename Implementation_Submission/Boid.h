#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef BOID_H_
#define BOID_H_

class myvector {

public:
    float x;
    float y;

    //Constructors
    myvector() {}

    myvector(float a, float b)
    {
        x = a;
        y = b;
    }

    void set(float x, float y);

    //Scalar functions scale a vector by a float
    void addVector(myvector v);
    void addScalar(float x);
    void subVector(myvector v);
    void subScalar(float x);

    void mulVector(myvector v);
    void mulScalar(float x);
    void divVector(myvector v);
    void divScalar(float x);

    void limit(double max);

    float distanceTwoVectors(myvector v);
    float dotProduct(myvector v);
    float magnitude();
    void setMagnitude(float x);
    float angle(myvector v);
    void normalize();

    myvector copy(myvector v);
};


class Boid {
public:
    myvector location;
    myvector velocity;
    myvector acceleration;
    float maxSpeed;
    float maxForce;
    Boid() {}
    Boid(float x, float y);
    void applyForce(myvector force);

    // Three Laws that boids follow
    myvector Separation(vector<Boid> Boids);
    myvector Alignment(vector<Boid> Boids);
    myvector Cohesion(vector<Boid> Boids);

    //Functions involving SFML
    myvector seek(myvector v);
    void run(vector <Boid> v,int a);
    void update();
    void flock(vector <Boid> v);
    void borders(int a);
    float angle(myvector v);
};

#endif
