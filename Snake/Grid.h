#pragma once

#include <SFML/Graphics.hpp>

#include <array>

#include "Window.h"

// Consts 
static const float CELL_SIZE = 16.0f;
static const int SPACE = 16;

// Grid class
class Grid
{
private:
	std::array<std::array<sf::RectangleShape, WINDOW_HEIGHT / SPACE>, WINDOW_WIDTH / SPACE> m_cells;

public:
	void Init(const sf::RenderWindow& window, const sf::Color& cellColor, const sf::Color& lineColor);
	void Draw(sf::RenderWindow& window);
	const sf::Vector2f& PlaceAt(const int posX, const int posY) const;
};