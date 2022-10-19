#pragma once

#include <SFML/Graphics.hpp>

// Consts
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;
static const std::string WINDOW_TITLE = "Snake eater";

// Window class
class Window
{
public:
	Window();
	~Window();

public:
	sf::RenderWindow window;

public:
	void Init(const int& width, const int& height, const std::string& title, const int&& limit);

	sf::Vector2f& GetMiddle();
};

