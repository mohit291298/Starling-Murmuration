#include <iostream>
#include <vector>
#include "Boid.h"
/** @file */
#ifndef FLOCK_H_
#define FLOCK_H_

/**
* Class for representing the flock(group) of starlings.
* This class uses the Boid class and is used to store the boids in the flock.
*/
class Flock {
public:
    vector<Boid> flock; /**< A public std::vector of Boids representing the floack as a whole.*/
     /**
    * A Constructor.
    * The default constructor(with no parameters).
    */   
    Flock() {}
    Boid getBoid(int i);
    void addBoid(Boid b);
    int getSize();
    void flocking(int a);
};

#endif
