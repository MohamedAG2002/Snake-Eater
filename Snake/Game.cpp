#include "Game.h"

#include "Window.h"
#include "GameObject.h"
#include "Grid.h"
#include "Score.h"
#include "State.h"

#include <vector>

/* Objects declarations */
Window window;
Grid grid;
State state;
std::vector<Snake> snake;
std::vector<sf::Vector2f> lastPosition;
std::vector<Apple> objects;

Game::Game()
{
	m_deltaTime = 0.0f;
	m_framesCounter = 0;
	m_font.loadFromFile("font/bit5x3.ttf");
}

Game::~Game()
{

}

void Game::Init()
{
	// Window init
	window.Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, 60);
	
	// Grid init
	grid.Init(window.window, sf::Color::Green, sf::Color::Green);

	// Snake head init
	Snake head(grid.PlaceAt(0, 0), sf::Vector2f(CELL_SIZE, CELL_SIZE), sf::Color::Black, true);
	head.SetMoving(false);
	snake.push_back(head);
	lastPosition.push_back(grid.PlaceAt(0, 0));

	// Apple init
	Apple apple(grid.PlaceAt((WINDOW_WIDTH / SPACE) / 2, (WINDOW_HEIGHT / SPACE) / 2), 
							{ CELL_SIZE / 2.0f, CELL_SIZE / 2.0f }, 
							sf::Color::Black, 
							true);
	objects.push_back(apple);
}

void Game::Update()
{
	// Calculating delta time
	m_deltaTime = m_deltaClock.restart().asSeconds();

	// Counting the frames
	m_framesCounter++;

	/* Movement handaling */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) snake.at(0).SetMoving(true);

	// Recording the last position of the tails
	for (int i = 0; i < lastPosition.size(); i++)
	{
		lastPosition.at(i) = snake.at(i).GetPos();
	}

	// Checking every 5 frames to make everything grid-based
	// Play with the numbers if you want to check
	if (m_framesCounter % 5 == 0 && state.GetState() == 1)
	{
		if (!state.IsPaused())
		{
			for (int i = 0; i < snake.size(); i++)
			{
				if (i == 0)
				{
					if (snake.at(0).IsMoving()) snake.at(0).Move(12.0f);
				}
				// Sets the position to the last position of the tail that is infront of it
				// Doing this so things can shift over instead of sticking to one another or staying still
				else snake.at(i).SetPos(lastPosition.at(i - 1));
			}
		}
	}

	/* Collision handaling */
	// Snake with the apple
	if (snake.at(0).GetCollider().intersects(objects.at(0).GetCollider()))
	{
		// Increase the score
		score.SetScore(score.GetScore() + 1);

		// Reposition the apple
		objects.at(0).SetPos(objects.at(0).GetNewPos(window.window));

		// Add to the tail
		// Setting the tail's position at a slight offset from the head to make collision easier
		Snake tail(snake.at(0).GetPos() + sf::Vector2f(0.4f, 0.2f), sf::Vector2f(CELL_SIZE, CELL_SIZE), sf::Color::Black, true);
		snake.push_back(tail);
		lastPosition.push_back(tail.GetPos());
	}

	// Snake with the walls
	if (snake.at(0).GetPos().x < -5 || snake.at(0).GetPos().x > window.window.getSize().x || snake.at(0).GetPos().y < -5
		|| snake.at(0).GetPos().y > window.window.getSize().y)
	{
		state.SetOver(true);
	}

	// The head with the tails, ignoring the head
	for (int i = 1; i < snake.size(); i++)
	{
		if ((snake.at(0).GetPos().x == snake.at(i).GetPos().x) && (snake.at(0).GetPos().y == snake.at(i).GetPos().y))
			state.SetOver(true);
	}

	/* Score handaling */
	// Setting the high score
	if (score.GetScore() > score.GetHighScore()) score.SetHighScore(score.GetScore());

	/* State handaling */
	state.Update();
}

void Game::Render()
{
	/* Rendering stuff */
	window.window.clear(sf::Color::Green);

	switch (state.GetState())
	{
		// Menu
		case MENU: state.Menu(window.window); break;
		// Game
		case GAME:
		{
			// Rendering the grid
			grid.Draw(window.window);

			// Rendering the apple
			if (objects.at(0).IsActive()) objects.at(0).Draw(window.window);

			// Rendering the snake
			for (auto& s : snake)
			{
				if (s.IsActive()) s.Draw(window.window);
			}

			// Setting the text
			sf::Text scoreText(std::to_string(score.GetScore()), m_font, 20);
			scoreText.setPosition(grid.PlaceAt((WINDOW_WIDTH / SPACE) / 2, 0));
			scoreText.setFillColor(sf::Color::Black);

			// Drawing the text
			window.window.draw(scoreText);
		} break;
		// Game over
		case OVER: state.Over(window.window); break;
	}

	// Managing the pause screen
	if (state.IsPaused()) state.Pause(window.window);

	window.window.display();
}

void Game::Reset()
{
	// Clearing the vectors to make way for the new one
	snake.clear();
	lastPosition.clear();

	// Player reset
	Snake head(grid.PlaceAt(0, 0), sf::Vector2f(CELL_SIZE, CELL_SIZE), sf::Color::Black, true);
	head.SetMoving(false);
	snake.push_back(head);
	lastPosition.push_back(head.GetPos());

	// Apple reset
	objects.at(0).SetPos(grid.PlaceAt((WINDOW_WIDTH / SPACE) / 2, (WINDOW_HEIGHT / SPACE) / 2));

	// Variables reset
	m_framesCounter = 0;
	score.SetScore(0);
	state.SetOver(false);
}

void Game::ProcessEvents()
{
	// Polling for events
	while (window.window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
			case sf::Event::Closed: window.window.close(); break;
			case sf::Event::KeyPressed:
			{
				if (m_event.key.code == sf::Keyboard::Escape) window.window.close();
			} break;
		}
	}
}

void Game::Run()
{
	// Initializes the game
	Init();

	// Main game loop
	while (window.window.isOpen())
	{
		ProcessEvents();

		// Handals the logic
		Update();

		// Handals the visuals
		Render();
	}
}