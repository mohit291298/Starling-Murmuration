#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;
/** @file */
#ifndef BOID_H_
#define BOID_H_

/**
* Class for representing Euclidian vectors.
* The vectors have both magnitude and direction.
* These are used to denote the location, velocity and acceleration of each starling.
*/
class myvector {

public:
    float x; /**< A public float member representing x-projection.*/
    float y; /**< A public float member representing y-projection.*/

    /**
    * A Constructor.
    * The default constructor(with no parameters).
    */
    myvector() {}

    /**
    * A Constructor.
    * The constructor initialies the vector.
    * @param a the x-projection.
    * @param b the y-projection.
    */
    myvector(float a, float b)
    {
        x = a;
        y = b;
    }

    void set(float x, float y);

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

/**
* Class for representing each boid(Starling).
* This class completely characterizes a starling.
* It consists of various data members like location, velocity, acceleration and many functions to maipulate these appropriately.
*/

class Boid {
public:
    myvector location;/**< A public vector representing the boid's location.*/

    myvector velocity; /**< A public vector representing the boid's velocity.*/
    
    myvector acceleration; /**< A public vector representing the boid's acceleration.*/

    float maxSpeed; /**< A public vector representing the maxspeed the boid can have(To impose realistic behaviour).*/
    
    float maxForce; /**< A public vector representing the maxforce the boid can experience(To impose realistic behaviour).*/
 
     /**
    * A Constructor.
    * The default constructor(with no parameters).
    */   
    Boid() {} 

    Boid(float x, float y);
    void applyForce(myvector force);

    // Three Laws that boids follow
    myvector Separation(vector<Boid> Boids);
    myvector Alignment(vector<Boid> Boids);
    myvector Cohesion(vector<Boid> Boids);

    void run(vector <Boid> v,int a);
    void update();
    void flock(vector <Boid> v);
    void borders(int a);
    float angle(myvector v);
};

#endif
