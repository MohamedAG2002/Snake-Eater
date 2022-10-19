#pragma once

#include <SFML/Graphics.hpp>

enum GameState { MENU = 0, GAME, OVER };

class State
{
public:
	State();
	~State();

private:
	bool m_isPaused, m_isGameOver;
	GameState m_currentState;

public:
	void Update();
	void Menu(sf::RenderWindow& window);
	void Pause(sf::RenderWindow& window);
	void Over(sf::RenderWindow& window);
	
	void SetPause(const bool& pause) { m_isPaused = pause; }
	const bool& IsPaused() const { return m_isPaused; }

	void SetOver(const bool& over) { m_isGameOver = over; }
	const bool& IsOver() const { return m_isGameOver; }

	const GameState& GetState() const { return m_currentState; }
};