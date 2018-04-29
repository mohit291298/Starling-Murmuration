#include <iostream>
#include "../include/Flock.h"
#include "../include/Boid.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

/** @file */

/**
* Class for doing the simulation and rendering using SFML
* This class handles all the input(eg. mouse clicks.).
* Handles all the program's interaction with SFML.
* This class contatins some private function requred for rendering and handling input too.
*/

class Simulate{
private:
	sf::RenderWindow window;

    int window_width;
    int window_height;

    float boids_mass_size;
    Flock flock;
    vector<sf::CircleShape> shapes;

    void Render(int a){
	    window.clear();

	    for (int i = 0; i < shapes.size(); i++) {
	        window.draw(shapes[i]);

	        shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);

	        // Calculates the angle where the velocity is pointing so that the triangle turns towards it.
	        float theta = flock.getBoid(i).angle(flock.getBoid(i).velocity);
	        shapes[i].setRotation(theta);

	        // Prevent boids from moving off the screen through wrapping
	        if (shapes[i].getPosition().x > window_width)
	            shapes[i].setPosition(shapes[i].getPosition().x - window_width, shapes[i].getPosition().y);
	        if (shapes[i].getPosition().y > window_height)
	            shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - window_height);
	        if (shapes[i].getPosition().x < 0)
	            shapes[i].setPosition(shapes[i].getPosition().x + window_width, shapes[i].getPosition().y);
	        if (shapes[i].getPosition().y < 0)
	            shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + window_height);
	    }

	    // Applies the three rules to each boid in the flock and changes them accordingly.
	    flock.flocking(a);

	    window.display();

    }
    void HandleInput(){
	    sf::Event event;
	    while (window.pollEvent(event)) {
	        if ((event.type == sf::Event::Closed) ||
	            (event.type == sf::Event::KeyPressed &&
	             event.key.code == sf::Keyboard::Escape) ||
	            (event.type == sf::Event::KeyPressed &&
	             event.key.code == sf::Keyboard::BackSpace) ||
	            (event.type == sf::Event::KeyPressed &&
	             event.key.code == sf::Keyboard::X))
	             {
	            window.close();
	        }
	    }

	    // Check for mouse click, draws and adds boid to flock if so.
	    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	        sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
	        Boid b(mouseCoords.x, mouseCoords.y);
	        sf::CircleShape shape(10,3);

	        shape.setPosition(mouseCoords.x, mouseCoords.y);
	        shape.setOutlineColor(sf::Color(0, 0, 255));
	        shape.setFillColor(sf::Color(0, 0, 255));
	        shape.setOutlineColor(sf::Color::White);
	        shape.setOutlineThickness(1);
	        shape.setRadius(boids_mass_size);

	        flock.addBoid(b);
	        shapes.push_back(shape);
	        Num_boids++;
	        cout<<"Number of Starlings:  "<<Num_boids<<"\n";
	        // New Shape is drawn
	        window.draw(shapes[shapes.size()-1]);
	    }

    }

public:

	int Num_boids; /**< A public int denoting number of starlings at any instant.*/

	/**
	* A Constructor.
	* The constructor constructs the window and sets up the required properties of simulation. 
	*/
	Simulate(){
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window_height = desktop.height;
    window_width  = desktop.width;

    boids_mass_size = 2.5;
    window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);

	}
	/**
	* A Member function which runs the simulation of starlings.
	* This simulates and displays the boids that we create and handles the reqired input.
	* @param a An int which is passed to the Boid class to do simulation either in
	* a wrap around manner(when a is non-zero) or confined to bounderies(when a = 0).
	* @see borders
	* @see Boid
	*/
	void Run(int a){
	    Num_boids = 225;
	    for (int i = 0; i < 225 ;i++) {
	        Boid b(window_width / 3, window_height / 3); // Starts all boids in the center of the screen
	        sf::CircleShape shape(8, 3);

	        // Changing the Visual Properties of the shape
	        // shape.setPosition(b.location.x, b.location.y); // Sets position of shape to random location that boid was set to.
	        shape.setPosition(window_width, window_height); // Testing purposes, starts all shapes in the center of screen.
	        shape.setOutlineColor(sf::Color(0,255,0));
	        shape.setFillColor(sf::Color::Green);
	        shape.setOutlineColor(sf::Color::White);
	        shape.setOutlineThickness(1);
	        shape.setRadius(boids_mass_size);

	        // Adding the boid to the flock and adding the shapes to the vector<sf::CircleShape>
	        flock.addBoid(b);
	        shapes.push_back(shape);
	    }
	    while (window.isOpen()) {
	        HandleInput();
	        Render(a);
	    }
		
	}
};

/**
* The main function.
* Takes various inputs from the user for a better visualisation of simulation.
* Call the Simulate class for execution which then takes care of subsequent simulation.
* @see Simulate
*/
int main()
{	
	cout<<"********************************************************************\n\n\n";
	cout<< "Starlings Murmuration refers to the phenomenon that results when hundreds of starlings fly in swooping, intricately coordinated patterns through the sky.\n\n\n";

	cout<<" So, let's see the simulation of a flock of starlings murmurtion!\n";

	cout<<"Do you want the to see the starlings in wrap- around manner(enter a non-zero value) or within a boundary(enter 0) ?\n";

	// cout<<"Enter the number of starlings you want in the flock:\n";
	int a;
	cin>>a;
    Simulate sim;
    sim.Run(a);
    return 0;
}
