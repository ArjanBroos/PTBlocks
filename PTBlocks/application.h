#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>

// The main application
class Application {
public:
	// Initializes the application
	Application(unsigned width, unsigned height, const std::string& title);

	// Handles input events
	void				HandleEvents();
	// Draws pixels to the window - assumes RGB format
	void				Draw(unsigned char* pixels, unsigned width, unsigned height);

	// Returns the width of the window
	unsigned			GetWidth() const;
	// Returns the height of the window
	unsigned			GetHeight() const;
	// Returns true if the application is still running
	bool				IsRunning() const;

private:
	sf::RenderWindow	window;		// The actual SFML window
	sf::Image			image;		// End image to create texture from
	sf::Texture			texture;	// The texture holding the end-image
	sf::Sprite			sprite;		// The sprite to draw texture with

	unsigned			width;		// Width of the SFML window
	unsigned			height;		// Height of the SFML window
};