#include "GameObject.h"
#include "Util.h"

/* Game object functions */
GameObject::GameObject(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color, const bool& active)
	:m_position(pos), m_size(size), m_color(color), m_isActive(active)
{}

GameObject::~GameObject()
{

}

void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(GetShape());
}

sf::RectangleShape& GameObject::GetShape()
{
	m_shape.setPosition(m_position);
	m_shape.setSize(m_size);
	m_shape.setFillColor(m_color);

	return m_shape;
}

sf::FloatRect& GameObject::GetCollider()
{
	if (m_isActive) return m_collider = sf::FloatRect(m_position, m_size);
	else return m_collider = sf::FloatRect();
}

/* Snake functions */
void Snake::Move(const float&& tileSpeed)
{
	/* Halfing all of the values to reduce its speed */

	// Moving up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_speed = { 0.0f, -tileSpeed };
	// Moving down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_speed = { 0.0f, tileSpeed };
	// Moving left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_speed = { -tileSpeed, 0.0f };
	// Moving right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_speed = { tileSpeed, 0.0f };

	m_position += m_speed;
}

/* Apple functions */
sf::Vector2f& Apple::GetNewPos(sf::RenderWindow& window)
{
	sf::Vector2f newPos;

	newPos.x = (float)utl::GetRand(10, window.getSize().x);
	newPos.y = (float)utl::GetRand(10, window.getSize().y);

	return newPos;
}