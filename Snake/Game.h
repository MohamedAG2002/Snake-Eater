#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
public:
	Game();
	~Game();

public:
	void Init();
	void Update();
	void Render();
	void Reset();
	void ProcessEvents();
	void Run();

	sf::Font& GetFont() { return m_font; }

private:
	sf::Clock m_deltaClock;
	float m_deltaTime;
	int m_framesCounter;
	sf::Event m_event;
	sf::Font m_font;
};

