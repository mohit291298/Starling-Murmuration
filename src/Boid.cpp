#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "../include/Boid.h"
/** @file */

// Global Variables for borders()
// desktopTemp gets screen resolution of PC running the program
sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

#define w_height window_height
#define w_width window_width
#define PI 3.141592635

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

/**
* A Member function which sets the fields of an object of class myvector.
* @param a A float representing the x component.
* @param b A float representing the y component.
*/
void myvector::set(float a, float b)
{
    x = a;
    y = b;
}

/**
* A Member function which adds a myvector object to the current object.
* Individually adds different components of the two vectors.
* @param v A vector(object) of the myvector class.
*/

void myvector::addVector(myvector v)
{
    x = x + v.x;
    y = y + v.y;
}

/**
* A Member function which subtracts a myvector object to the current object.
* Individually subtracts different components of the two vectors.
* @param v A vector(object) of the myvector class.
*/
void myvector::subVector(myvector v)
{
    x = x - v.x;
    y = y - v.y;
}

/**
* A Member function which adds a scalar( type float) from the current object.
* Individually increments different components of the myvetor object by the input scalar.
* @param a A float to be added.
*/

void myvector::addScalar(float a)
{
    x = x + a;
    y = y + a;
}

/**
* A Member function which subtracts a scalar( type float) from the current object.
* Individually decrements different components of the myvetor object by the input scalar.
* @param a A float to be subtracted.
*/

void myvector::subScalar(float a)
{
    x = x - a;
    y = y - a;
}

/**
* A Member function which multiplies a scalar( type float) to the current object.
* Individually multiplies different components of the myvetor object by the input scalar.
* @param a A float to be multiplied.
*/

void myvector::mulScalar(float a)
{
    x = x*a;
    y = y*a;
}

/**
* A Member function which multiplies a myvector object to the current object.
* Individually multiplies different components of the two vectors.
* @param v A vector(object) of the myvector class.
* This function may be used when we want to scale differnt components by diff values in a go.
*/
void myvector::mulVector(myvector v)
{
    x = x*(v.x);
    y = y*(v.y);
}

/**
* A Member function which divides a scalar( type float) to the current object.
* Individually divides different components of the myvetor object by the input scalar.
* @param a A float to be divided by.
*/
void myvector::divScalar(float a)
{
    x = x/a;
    y = y/a;
}

/**
* A Member function which divides a myvector object to the current object.
* Individually divides different components of the two vectors.
* @param v A vector(object) of the myvector class.
* This function may be used when we want to scale differnt components by diff values in a go.
*/
void myvector::divVector(myvector v)
{
    x = x/(v.x);
    y = y/(v.y);
}

/**
* A Member function which limits the magnitude of a myvector object by a constant value. 
* Checks if magnitude of myvector is greter than the input value.
* IF yes, the divides each component by that value else no chang
* @param max A double which is used limit the myvector.
*/
void myvector::limit(double max)
{
    double s = sqrt(x*x + y*y);
    if(s > max){
    	set(x / s, y / s);
    }
}

/**
* A Member function which computes the distance between two myvectors. 
* Calculates the distance between the input myvector and the current myvector.
* @param max An object of myvector class.
* @return dist:The required distance of type float.
*/
float myvector::distanceTwoVectors(myvector v)
{

	float dist = sqrt(((x - v.x)*(x - v.x)) + ((y - v.y)*(y - v.y)));
	return dist;
}

/**
* A Member function which computes the magnitude of the myvector object. 
* @return A float representing the magnitude.
*/
float myvector::magnitude()
{
    return sqrt(x*x + y*y);
}

/**
* A Member function which calculates dot product of two vectors.
* Calculates dot product of the object vector and the arguement vector and returns a float value.
* @param v A vector.
* @return The dot product(float value).
*/
float myvector::dotProduct(myvector v)
{
	float a = x*(v.x) + y*(v.y);
	return a;
}

/**
* A Member function which creates a copy of the input vector.
* @return The copy of the input vector.
*/
myvector myvector::copy(myvector v)
{
    return v;
}

/**
* A Member function which normalizes the current vector.
*It modifies the vector to make it a unit magnitude vector.
*/
void myvector::normalize()
{
	float mag = magnitude();

	if(mag > 0){
		set(x/mag,y/mag);
	}
	else{
		set(x,y);
	}
}

/**
* A Member function which modifies the vector to have a particualr magnitude.
* So this function enlarges or diminishes the vector appropriately by a given a constant.
* @param x A float to be set as the magnitude.
* @see normalize
* @see mulscalar
*/
void myvector::setMagnitude(float x)
{
    normalize();
    mulScalar(x);
}

/**
* A Member function which computes the angle(in radians) between two vectors.
* @param v A vector whose angle with the current vector is to be calculated.
* @return A float representing th angle between the two vectors.
*/
float myvector::angle(myvector v)
{
	    if (x == 0 && y == 0) return 0.0f;
    if (v.x == 0 && v.y == 0) return 0.0f;

    double dotprod = x * v.x + y * v.y;
    double m1 = magnitude();
    double m2 = sqrt(v.x * v.x + v.y * v.y);
    double amt = dotprod / (m1 * m2); 
    if (amt <= -1) {
        return PI;
    } else if (amt >= 1) {
        return 0;
    }
    float temp = acos(amt);
    return temp;

}

/**
* A Constructor.
* The constructor initialies the a boid(Starling).
* Initializes the location, acceleration and velocity of the boid.
* Also defines the maxforce and maxspeed for realistic values.
*/
Boid::Boid(float x, float y)
{
    location = myvector(x, y);
    velocity = myvector(rand()%3 - 2, rand()%3 - 2);
    acceleration = myvector(0, 0);
    maxSpeed = 3.5;
    maxForce = 0.5;
}

/**
* A Member function which adds a particualr force to the boid.
* So this function the force vector to the current acceleration vector.
* @param force The force vector( an object of myvector)
*/
void Boid::applyForce(myvector force)
{
    acceleration.addVector(force);
}

/**
* A Member function implementing the ALIGNMENT Boid rule!
* This function instead of affecting the position of the boid,
* changes the velocity of the boid and add up the velocity of
* all the neighbouring boids, and divide it by the number of neighbours.
* The final value modifies the velocity instead of replacing it altogether.
* @param boids A vector<Boid> of boids.
* @return A vector which is the steer vector(Desired - Velocity).
*/
myvector Boid::Alignment(vector<Boid> boids){

    float neighborradius = 50;

    int count = 0;
    myvector s(0,0);

    for(int i=0; i <boids.size();i++){
        float dist = location.distanceTwoVectors(boids[i].location);

        if((dist > 0) && (dist <neighborradius)){
            count++;
            s.addVector(boids[i].velocity);
        }
    }
    myvector move;
    myvector temp(0,0);
    if(count > 0 ){
        s.divScalar((float)count);
        s.normalize();
        s.mulScalar(maxSpeed);
        //Steer = Desired - Velocity
        s.subVector(velocity);
        move.set(s.x,s.y);
        move.limit(maxForce);
        return move;
    }
    else{
        return temp;
    }
}

/**
* A Member function implementing the SEPARATION Boid rule!
* This rule says that the birds have to avoid collision with its neighbours.
* For this we have to consider a collision radius desiredsepartion such that for a bird if
* there is any neighbour in this radius then the bird has to go away from
* that neighbour.
* @param boids A vector<Boid> of boids.
* @return A vector which is the steer vector(Desired - Velocity).
*/
myvector Boid::Separation(vector<Boid> boids)
{
    float desiredseparation = 20;
    myvector move(0, 0);
    int count = 0;
    for (int i = 0; i < boids.size(); i++) {
        float d = location.distanceTwoVectors(boids[i].location);
        if ((d > 0) && (d < desiredseparation)) {
            myvector diff(0,0);
            diff.set((location.x - boids[i].location.x),(location.y - boids[i].location.y));
            diff.normalize();
            diff.divScalar(d);      
            move.addVector(diff);
            count++;
        }
    }
    if (count > 0)
        move.divScalar((float)count);
    if (move.magnitude() > 0) {
        move.normalize();
        move.mulScalar(maxSpeed);
        move.subVector(velocity);
        move.limit(maxForce);
    }
    return move;
}

/**
* A Member function implementing the COHESHION Boid rule!
* Finds the average location of nearby boids and manipulates the
* steering force to move in that direction.
* @param boids A vector<Boid> of boids.
* @return A vector which is the steer vector(Desired - Velocity).
*/
myvector Boid::Cohesion(vector<Boid> boids){

    float neighborradius = 50;

    int count = 0;
    myvector s(0,0);

    for(int i=0; i <boids.size();i++){
        float dist = location.distanceTwoVectors(boids[i].location);

        if((dist > 0) && (dist <neighborradius)){
            count++;
            s.addVector(boids[i].location);
        }
    }
    myvector temp(0,0);
    if(count > 0 ){
        s.divScalar((float)count);
        s.normalize();
        s.mulScalar(maxSpeed);
        s.subVector(velocity);
        //acceleration.set(s.x,s.y);
        acceleration.limit(maxForce);  // Limit to maximum steering force
        return acceleration;
    }
    else{
        return temp;
    }
}

/**
* A Member function which updated the parameters of the boid in response to its environment.
* This modifies the location, velocity and also resets the accelration
* according to the values returned by the the three boid rules.
*/
void Boid::update()
{
    acceleration.mulScalar(.4);
    velocity.addVector(acceleration);
    velocity.limit(maxSpeed);
    location.addVector(velocity);
    acceleration.mulScalar(0);
}

/**
* A Member function which updated the parameters of the all the boids and applies the rules on them.
* This function updates the behaviour of the all the boids.
* @param v The vector of the Boid at the current instant.
* @param a An int specifying wrap around or boundary simulation. 
* @see flock
* @see update
* @see borders
*/
void Boid::run(vector <Boid> v,int a)
{
    flock(v);
    update();
    borders(a);
}

/**
* A Member function which computes the angle of velocity so that image roates appropriately
* in the direction of motion
* Tan inverse x/y is returned in degrees.
* @param v The myvector on which computation is to be done.
* @return A float representing the angle in degrees.
*/
float Boid::angle(myvector v)
{
    float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
    return angle;
}

/**
* A Member function which applies the three laws to the flock of boids.
* This then also assigns factors(weightage) to different laws.
* @param v The vector of the Boid at the current instant. 
* @see Separation
* @see Cohesion
* @see Alignment
*/
void Boid::flock(vector<Boid> v)
{
    myvector separate = Separation(v);
    separate.mulScalar(1.5);

    myvector align = Alignment(v);    
    align.mulScalar(1.0); // Might need to alter weights for different characteristics

    myvector coh = Cohesion(v);
    coh.mulScalar(1.0);
  
    applyForce(separate);
    applyForce(align);
    applyForce(coh);
}

/**
* A Member functionis used to handle if a bird goes out of window.
* Depending on the input it eitheer implements wrap around or the boundary condition.
* @param a An in which is non-zero when use wants wrap-around simulation else 0 when 
* Boundary conditions are imposed. 
*/
void Boid::borders(int a)
{
    if(a!=0){
        if (location.x < 0)    location.x += w_width;
        if (location.y < 0)    location.y += w_height;
        if (location.x > 1000) location.x -= w_width;
        if (location.y > 1000) location.y -= w_height;
    }
    else{
        if (location.x < 1)    velocity.set(-(velocity.x), (velocity.y));
        if (location.y < 1)    velocity.set((velocity.x), -(velocity.y));
        if (location.x > 900) velocity.set(-(velocity.x), (velocity.y));
        if (location.y > 900) velocity.set((velocity.x), -(velocity.y));
    }
}
