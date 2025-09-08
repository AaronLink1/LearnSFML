#include <SFML/Graphics.hpp>
#include <cmath>
#include <numbers>
#include <iostream>

constexpr double RAD_TO_DEG (180.0 / std::numbers::pi);

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1980, 1080 }), "SFML Learning Vectors");
	window.setVerticalSyncEnabled(true);

	//sf::Clock gameClock;

	sf::RectangleShape rect({0.0f, 5.0f});
	rect.setOrigin({ 0.0f, rect.getSize().y / 2.0f });
	rect.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
	rect.setFillColor(sf::Color::Red);
	rect.setOutlineThickness(1.0f);
	rect.setOutlineColor(sf::Color::Black);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
				switch (keyPressed->scancode)
				{
				case sf::Keyboard::Scancode::Escape:
					window.close();
					break;
				}
			//else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			//{
			//	mouseClick = sf::Vector2f{ mousePressed->position };
			//	//std::cout << "(" << mouseClick.x << ", " << mouseClick.y << ")" << std::endl;
			//	rect.setSize(mouseClick);
			//}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2f mousePosition = sf::Vector2f{ sf::Mouse::getPosition(window) };
			sf::Vector2f direction = mousePosition - rect.getPosition();
			rect.setSize({ std::hypotf(direction.x, direction.y), rect.getSize().y });
			rect.setRotation(sf::degrees(std::atan2(direction.y, direction.x) * RAD_TO_DEG));
		}

		window.clear(sf::Color::Cyan);
		window.draw(rect);
		window.display();
	}

	return 0;
}