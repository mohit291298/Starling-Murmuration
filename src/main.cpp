#include <iostream>
#include "../include/Flock.h"
#include "../include/Boid.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
//#include <Text.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>
#include <sstream> 

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
    sf::Font font;
	sf::Text atext;
	sf::Text atext2;
	sf::Text atext3;
	sf::Text atext4;
	sf::Text atext5;
	sf::Text atext6;
	sf::Text atext7;

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


// Load it from a file

std::ostringstream ss; //string buffer to convert numbers to string
ss << "Total Energy: " << flock.energy;// put float into string buffer


//set up text properties

atext.setString(ss.str()); //ss.str() converts the string buffer into a regular string 
std::ostringstream ss2; //string buffer to convert numbers to string
ss2 << "Average Energy : " << ((flock.energy)/Num_boids);// put float into string buffer
std::ostringstream ss3; //string buffer to convert numbers to string
ss3 << "Number of Boids : " << Num_boids;// put float into string buffer

std::ostringstream ss4; //string buffer to convert numbers to string
ss4 << "Total Force : " << flock.force;// put float into string buffer
std::ostringstream ss5; //string buffer to convert numbers to string
ss5 << "Average Force : " << ((flock.force)/Num_boids);// put float into string buffer

std::ostringstream ss6; //string buffer to convert numbers to string
ss6 << "Total Angular Momentum : " << flock.angmomentum;// put float into string buffer
std::ostringstream ss7; //string buffer to convert numbers to string
ss7 << "Average Angular Momentum : " << ((flock.angmomentum)/Num_boids);// put float into string buffer

//set up text properties

atext2.setString(ss2.str()); //ss.str() converts the string buffer into a regular string 
atext3.setString(ss3.str()); //ss.str() converts the string buffer into a regular string 
atext4.setString(ss4.str()); //ss.str() converts the string buffer into a regular string 
atext5.setString(ss5.str()); //ss.str() converts the string buffer into a regular string 
atext6.setString(ss6.str()); //ss.str() converts the string buffer into a regular string 
atext7.setString(ss7.str()); //ss.str() converts the string buffer into a regular string 

//draw the string
window.draw(atext);
window.draw(atext2);
window.draw(atext3);
window.draw(atext4);
window.draw(atext5);
window.draw(atext6);
window.draw(atext7);

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

    boids_mass_size = 3;
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
	    if (!font.loadFromFile("arial.ttf"))
		    //find this file in the "pong" example in the SFML examples folder
		{
		    std::cout << "Error loading font\n" ;
		}
		atext.setFont(font);
		atext.setCharacterSize(20);
		atext.setStyle(sf::Text::Bold);
		atext.setColor(sf::Color::White);
		atext.setPosition(0,0);
		atext2.setFont(font);
		atext2.setCharacterSize(20);
		atext2.setStyle(sf::Text::Bold);
		atext2.setColor(sf::Color::White);
		atext2.setPosition(0,20);
		atext3.setFont(font);
		atext3.setCharacterSize(20);
		atext3.setStyle(sf::Text::Bold);
		atext3.setColor(sf::Color::White);
		atext3.setPosition(1500,0);
		atext4.setFont(font);
		atext4.setCharacterSize(20);
		atext4.setStyle(sf::Text::Bold);
		atext4.setColor(sf::Color::White);
		atext4.setPosition(0,950);
		atext5.setFont(font);
		atext5.setCharacterSize(20);
		atext5.setStyle(sf::Text::Bold);
		atext5.setColor(sf::Color::White);
		atext5.setPosition(0,970);
		atext6.setFont(font);
		atext6.setCharacterSize(20);
		atext6.setStyle(sf::Text::Bold);
		atext6.setColor(sf::Color::White);
		atext6.setPosition(1400,950);
		atext7.setFont(font);
		atext7.setCharacterSize(20);
		atext7.setStyle(sf::Text::Bold);
		atext7.setColor(sf::Color::White);
		atext7.setPosition(1400,970);

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
	    Num_boids = 350;
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
