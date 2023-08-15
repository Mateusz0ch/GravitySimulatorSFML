#include "Game.h"

Game::Game()
{
}
void Game::render()
{
	window->clear(sf::Color::Green);
	drawRectangles();
	window->display();
}
void Game::update()
{
	gravity();
}
void Game::startGame()
{
	window = new sf::RenderWindow(sf::VideoMode(640, 640), "Gravity", sf::Style::Default);
	window->setFramerateLimit(120);
	while (window->isOpen()) {
		eventHandler(ev);
		update();		
		gravity();
		render();
	}
}

void Game::addRectangle()
{
	sf::RectangleShape shape;
	int x_m = sf::Mouse::getPosition().x;
	int y_m = sf::Mouse::getPosition().y;
	int x_frame = window->getPosition().x;
	int y_frame = window->getPosition().y;
	shape.setPosition(sf::Vector2f(x_m-x_frame,y_m-y_frame));
	shape.setSize(sf::Vector2f(32,32));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setFillColor(sf::Color::Red);
	rectangles.push_back(shape);
	
}

void Game::drawRectangles()
{
	for (auto r : rectangles) {
		window->draw(r);
	}
}


void Game::eventHandler(sf::Event ev)
{
	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code==sf::Keyboard::A) {
				addRectangle();
				break;
			}
		}
	}
}

void Game::gravity()
{
	for (auto& r1 : rectangles) {
		bool isCollision = false;
		for (auto& r2 : rectangles) {
			if (&r1 != &r2) {
				sf::FloatRect rect1 = r1.getGlobalBounds();
				sf::FloatRect rect2 = r2.getGlobalBounds();
				int y = r1.getPosition().y;
				if (rect1.intersects(rect2)) {
					std::cout << "Intersected" << std::endl;
					isCollision = true;
				}
				else if (y + 32 > 640) {
					std::cout << "On bottom" << std::endl;
					isCollision = true;
				}
			}
		}
		if (!isCollision)
			r1.move(0, 1);
	}
}

bool Game::areRectanglesCollision(sf::RectangleShape& r1, sf::RectangleShape& r2)
{
	sf::FloatRect rect1bounds = r1.getGlobalBounds();
	sf::FloatRect rect2bounds = r2.getGlobalBounds();
	return rect1bounds.intersects(rect2bounds);
}
