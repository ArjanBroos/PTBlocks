#include "application.h"

#include <iostream>

// Initializes the application
Application::Application(unsigned width, unsigned height, const std::string& title)
	: window(sf::VideoMode(width, height), title.c_str()) {
}

// Handles input events
void Application::HandleEvents() {
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type) 
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			}
			break;
		}

	}
}

// Handles continuous pressed keys
void Application::pollKeyboard(Camera& camera, bool& moved) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		camera.Walk(.1f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		camera.Walk(-.1f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		camera.Strafe(-.1f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		camera.Strafe(.1f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		camera.Elevate(.1f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		camera.Elevate(-.1f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		camera.Yaw(.05f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		camera.Yaw(-.05f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		camera.Pitch(.05f);
		moved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		camera.Pitch(-.05f);
		moved = true;
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

// Sets the title
void Application::SetTitle(const std::string& title) {
	window.setTitle(title);
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