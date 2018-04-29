#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "Boid.h"

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
void myvector::set(float a, float b)
{
    x = a;
    y = b;
}

void myvector::addVector(myvector v)
{
    x = x + v.x;
    y = y + v.y;
}

void myvector::subVector(myvector v)
{
    x = x - v.x;
    y = y - v.y;
}

void myvector::subScalar(float a)
{
    x = x - a;
    y = y - a;
}

void myvector::mulScalar(float a)
{
    x = x*a;
    y = y*a;
}

void myvector::mulVector(myvector v)
{
    x = x*(v.x);
    y = y*(v.y);
}

void myvector::divScalar(float a)
{
    x = x/a;
    y = y/a;
}

void myvector::divVector(myvector v)
{
    x = x/(v.x);
    y = y/(v.y);
}

void myvector::limit(double max)
{
    double s = sqrt(x*x + y*y);
    if(s > max){
    	set(x / s, y / s);
    }
}

float myvector::distanceTwoVectors(myvector v)
{

	float dist = sqrt(((x - v.x)*(x - v.x)) + ((y - v.y)*(y - v.y)));
	return dist;
}

float myvector::magnitude()
{
    return sqrt(x*x + y*y);
}

float myvector::dotProduct(myvector v)
{
	float a = x*(v.x) + y*(v.y);
	return a;
}

myvector myvector::copy(myvector v)
{
    return v;
}

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

void myvector::setMagnitude(float x)
{
    normalize();
    mulScalar(x);
}


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

Boid::Boid(float x, float y)
{
    location = myvector(x, y);
    velocity = myvector(rand()%3 - 2, rand()%3 - 2);
    acceleration = myvector(0, 0);
    maxSpeed = 3.5;
    maxForce = 0.5;
}


// Adds force myvector to current force myvector
void Boid::applyForce(myvector force)
{
    acceleration.addVector(force);
}

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


// Modifies velocity, location, and resets acceleration with values that
// are given by the three laws.
void Boid::update()
{
    acceleration.mulScalar(.4);
    velocity.addVector(acceleration);
    velocity.limit(maxSpeed);
    location.addVector(velocity);
    acceleration.mulScalar(0);
}

void Boid::run(vector <Boid> v,int a)
{
    flock(v);
    update();
    borders(a);
}

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
// void boidrules::wrapup_boids(){if(location.x < 0)  {/location.x = location.x + w;/velocity =vectorfunc(-(rand()%3 - 2), -(rand()%3 - 2));} if(location.y < 0)    {/location.y = location.y + h;/velocity =vectorfunc(-(rand()%3 - 2), -(rand()%3 - 2));}
//                                if(location.x > 1850){/location.x = location.x - w;/velocity =vectorfunc((rand()%3 - 2), (rand()%3 - 2));} if(location.y > 1020){/location.y = location.y - h;/velocity =vectorfunc((rand()%3 - 2), (rand()%3 - 2));}
                              
//                               }

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

float Boid::angle(myvector v)
{
    float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
    return angle;
}
