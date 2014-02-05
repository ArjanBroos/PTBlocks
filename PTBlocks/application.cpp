#include "application.h"

#include <iostream>

// Initializes the application
Application::Application(unsigned width, unsigned height, const std::string& title)
	: window(sf::VideoMode(width, height), title.c_str()) {
}

// Handles input events
void Application::HandleEvents() {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window.close();
	}
}

// Draws to the window
void Application::Draw(unsigned char* pixels, unsigned width, unsigned height) {
	// Convert to SFML texture
	image.create(width, height, pixels);
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	window.clear();
	window.draw(sprite);
	window.display();
}

// Returns the width of the window
unsigned Application::GetWidth() const {
	return width;
}

//! Returns the height of the window
unsigned Application::GetHeight() const {
	return height;
}

// Returns true if the application is still running
bool Application::IsRunning() const {
	return window.isOpen();
}