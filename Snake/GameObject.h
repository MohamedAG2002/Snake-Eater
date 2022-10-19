#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"

// Main game object class
class GameObject
{
protected:
	sf::Vector2f m_position, m_size;
	sf::Color m_color;
	bool m_isActive;
	sf::RectangleShape m_shape;
	sf::FloatRect m_collider;

public:
	GameObject(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color, const bool& active);
	~GameObject();

public:
	void Draw(sf::RenderWindow& window);

	/* Getters and setters */
	// Position
	void SetPos(const sf::Vector2f& pos) { m_position = pos; }
	void SetPos(const float& posX, const float& posY) { m_position = sf::Vector2f(posX, posY); }
	const sf::Vector2f& GetPos() const { return m_position; }

	// Size 
	void SetSize(const sf::Vector2f& size) { m_size = size; }
	const sf::Vector2f& GetSize() const { return m_size; }

	// Color
	void SetColor(const sf::Color& color) { m_color = color; }
	const sf::Color& GetColor() const { return m_color; }

	// Active state
	void SetActive(const bool& active) { m_isActive = active; }
	const bool& IsActive() const { return m_isActive; }

	// Shape
	sf::RectangleShape& GetShape();

	// Collider
	sf::FloatRect& GetCollider();
};

// Snake class
class Snake : public GameObject
{
public:
	using GameObject::GameObject;

private:
	sf::Vector2f m_speed;
	bool m_isMoving;

public:
	void Move(const float&& tileSpeed);

	/* Getters and setters */
	// Speed
	void SetSpeed(const sf::Vector2f& speed) { m_speed = speed; }
	const sf::Vector2f& GetSpeed() const { return m_speed; }

	// Moving state
	void SetMoving(const bool& moving) { m_isMoving = moving; }
	const bool& IsMoving() const { return m_isMoving; }
};

// Apple class
class Apple : public GameObject
{
public:
	using GameObject::GameObject;

public:
	sf::Vector2f& GetNewPos(sf::RenderWindow& window);
};