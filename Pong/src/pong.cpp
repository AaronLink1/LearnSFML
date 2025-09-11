#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1980, 1080 }), "Pong Game");
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Clock gameClock;
	gameClock.start();

	sf::RectangleShape bat({ 10.0f, 220.0f });
	//bat.setOrigin(bat.getGeometricCenter());
	bat.setPosition({ 100.0f, window.getSize().y / 2.0f - bat.getSize().y / 2.0f});
	bat.setFillColor(sf::Color::Cyan);
	bat.setOutlineThickness(2.0f);
	bat.setOutlineColor(sf::Color::Black);

	bool moveUp = false, moveDown = false;
	sf::Vector2f velocity{ 0.0f, 20.0f };

	sf::CircleShape ball(10.0f);
	//ball.setOrigin(ball.getGeometricCenter());
	ball.setPosition({ window.getSize().x / 2.0f - 5.0f, window.getSize().y / 2.0f - 5.0f });
	ball.setFillColor(sf::Color::Blue);
	ball.setOutlineThickness(2.0f);
	ball.setOutlineColor(sf::Color::Black);

	float random = rand() % 20;
	sf::Vector2f ballVelocity = { -7.0f, 10.0f };

	while (window.isOpen())
	{
		gameClock.restart();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				switch (keyPressed->scancode)
				{
				case sf::Keyboard::Scancode::Escape:
					window.close();
					break;
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
			moveUp = true;
		else
			moveUp = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
			moveDown = true;
		else
			moveDown = false;

		if (moveUp && bat.getPosition().y > 0)
			bat.move(-velocity);
		else if (moveDown && (bat.getPosition().y + bat.getSize().y) < window.getSize().y)
			bat.move(velocity);

		if (ball.getPosition().y < 0)
			ballVelocity.y = -ballVelocity.y;
		else if (ball.getPosition().y + ball.getRadius() > window.getSize().y)
			ballVelocity.y = -ballVelocity.y;
		else if (ball.getPosition().x < -10)
			ball.setPosition({ window.getSize().x / 2.0f - 5.0f, window.getSize().y / 2.0f - 5.0f });
		else if (ball.getPosition().x + ball.getRadius() > window.getSize().x)
			ballVelocity.x = -ballVelocity.x;
		else if (ball.getGlobalBounds().findIntersection(bat.getGlobalBounds()))
			ballVelocity.x = -ballVelocity.x;

		ball.move(ballVelocity);

		window.clear(sf::Color::White);
		window.draw(bat);
		window.draw(ball);
		window.display();
	}
}