#include "State.h"
#include "Game.h"
#include "Util.h"
#include "Score.h"

/* Global variables */
Game game;
float opaque = 0;

State::State()
{
	m_isPaused = false;
	m_isGameOver = false;
	m_currentState = MENU;
}

State::~State()
{

}

void State::Update()
{
	// Menu to game
	if (m_currentState == MENU && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_currentState = GAME;
		game.Reset();
	}
	// Game to pause(and then back)
	if (m_currentState == GAME && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) m_isPaused = !m_isPaused;
	// Pause to menu
	if (m_isPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) m_currentState = MENU;
	// Game to over
	if (m_currentState == GAME && m_isGameOver)
	{
		opaque = 0;
		m_currentState = OVER;
	}
	// Over to game
	if (m_isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_currentState = GAME;
		game.Reset();
	}
}

void State::Menu(sf::RenderWindow& window)
{
	// Menu title
	sf::Text menuTitle("Snake Eater!", game.GetFont(), 50);
	menuTitle.setPosition(window.getSize().x / 2.0f - menuTitle.getGlobalBounds().width / 2.0f, 10.0f);
	menuTitle.setFillColor(sf::Color::Black);

	// Play text
	sf::Text playText("1.Play", game.GetFont(), 30);
	playText.setPosition(window.getSize().x / 2.0f - playText.getGlobalBounds().width / 2.0f, 177);
	playText.setFillColor(sf::Color::Black);

	// Exit text
	sf::Text exitText("[ESC] Exit", game.GetFont(), 20);
	exitText.setPosition(5, 455);
	exitText.setFillColor(sf::Color::Black);

	// Drawing the texts
	window.draw(menuTitle);
	window.draw(playText);
	window.draw(exitText);

	m_isPaused = false;
}

void State::Pause(sf::RenderWindow& window)
{
	// Pause title
	sf::Text pauseTitle("PAUSED", game.GetFont(), 30);
	pauseTitle.setPosition(window.getSize().x / 2.0f - pauseTitle.getGlobalBounds().width / 2.0f, 195);
	pauseTitle.setFillColor(sf::Color::Black);

	// Menu text
	sf::Text menuText("[M] Menu", game.GetFont(), 20);
	menuText.setPosition(5, 455);
	menuText.setFillColor(sf::Color::Black);

	// Drawing the texts
	window.draw(pauseTitle);
	window.draw(menuText);
}

void State::Over(sf::RenderWindow& window)
{
	// Clamping the opaque
	opaque = utl::Clamp(opaque, 0, 255);

	// Game over title
	sf::Text overTitle("GAME OVER!", game.GetFont(), 50);
	overTitle.setPosition(window.getSize().x / 2.0f - overTitle.getGlobalBounds().width / 2.0f, 10.0f);
	overTitle.setFillColor(sf::Color(0, 0, 0, (int)opaque));

	// Score text
	sf::Text scoreText("Score: " + std::to_string(score.GetScore()), game.GetFont(), 30);
	scoreText.setPosition(window.getSize().x / 2.0f - scoreText.getGlobalBounds().width / 2.0f, 147);
	scoreText.setFillColor(sf::Color::Black);

	// High score text
	sf::Text highScoreText("High Score: " + std::to_string(score.GetHighScore()), game.GetFont(), 30);
	highScoreText.setPosition(window.getSize().x / 2.0f - highScoreText.getGlobalBounds().width / 2.0f, 197);
	highScoreText.setFillColor(sf::Color::Black);

	// Replay text
	sf::Text replayText("[R] Replay", game.GetFont(), 20);
	replayText.setPosition(5, 455);
	replayText.setFillColor(sf::Color::Black);

	// Drawing the texts
	window.draw(overTitle);
	window.draw(scoreText);
	window.draw(highScoreText);
	window.draw(replayText);

	opaque += 2;

	m_isPaused = false;
}