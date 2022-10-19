#include "Window.h"

Window::Window()
{

}

Window::~Window()
{

}

void Window::Init(const int& width, const int& height, const std::string& title, const int&& limit)
{
	window.create(sf::VideoMode(width, height), title);
	window.setFramerateLimit(limit);
}

sf::Vector2f& Window::GetMiddle()
{
	sf::Vector2f middle;

	middle.x = window.getSize().x / 2.0f;
	middle.y = window.getSize().y / 2.0f;

	return middle;
}