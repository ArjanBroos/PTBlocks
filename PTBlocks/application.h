#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include "camera.h"

// The main application
class Application {
public:
	// Initializes the application
	Application(unsigned width, unsigned height, const std::string& title);

	// Handles input events
	void				HandleEvents();
	// Handles continuous pressed keys
	void				pollKeyboard(Camera& camera, bool& moved);
	// Draws pixels to the window - assumes RGB format
	void				Draw(unsigned char* pixels, unsigned width, unsigned height);
	// Sets the title of the window
	void				SetTitle(const std::string& title);

	// Returns the width of the window
	unsigned			GetWidth() const;
	// Returns the height of the window
	unsigned			GetHeight() const;
	// Returns true if the application is still running
	bool				IsRunning() const;

private:
	sf::RenderWindow	window;		// The actual SFML window
	sf::Image			image;		// End image to create texture from
	sf::Image			image2;		// End image to create texture from
	sf::Texture			texture;	// The texture holding the end-image
	sf::Sprite			sprite;		// The sprite to draw texture with
	sf::Texture			texture2;	// The texture holding the end-image
	sf::Sprite			sprite2;		// The sprite to draw texture with

	unsigned			width;		// Width of the SFML window
	unsigned			height;		// Height of the SFML window
};