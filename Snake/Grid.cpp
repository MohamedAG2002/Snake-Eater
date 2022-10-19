#include "Grid.h"

void Grid::Init(const sf::RenderWindow& window, const sf::Color& cellColor, const sf::Color& lineColor)
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		for (int j = 0; j < m_cells.at(i).size(); j++)
		{
			m_cells.at(i).at(j).setPosition(CELL_SIZE * i, CELL_SIZE * j);
			m_cells.at(i).at(j).setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			m_cells.at(i).at(j).setFillColor(cellColor);
			m_cells.at(i).at(j).setOutlineColor(lineColor);
			m_cells.at(i).at(j).setOutlineThickness(2.0f);
		}
	}
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		for (int j = 0; j < m_cells.at(i).size(); j++)
		{
			window.draw(m_cells.at(i).at(j));
		}
	}
}

const sf::Vector2f& Grid::PlaceAt(const int posX, const int posY) const 
{
	return m_cells.at(posX).at(posY).getPosition();
}