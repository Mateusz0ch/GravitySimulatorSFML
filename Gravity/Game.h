#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#define WIDTH 640
#define HEIGHT 640
#define TILE 16;
class Game
{
public:
	sf::RenderWindow* window;
	sf::Event ev;
	std::vector<sf::RectangleShape>rectangles;
	sf::CircleShape* circle;
	Game();
	void render();
	void update();
	void startGame();
	void addRectangle();
	void drawRectangles();
	void eventHandler(sf::Event ev);
	void gravity();
	bool areRectanglesCollision(sf::RectangleShape&r1,sf::RectangleShape&r2);
};

