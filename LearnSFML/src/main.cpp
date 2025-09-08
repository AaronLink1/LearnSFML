#include <SFML/Graphics.hpp>
#include <cmath>
#include <numbers>
#include <iostream>
#include <sstream>

constexpr double RAD_TO_DEG (180.0 / std::numbers::pi);

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1980, 1080 }), "SFML Learning Vectors");
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape rect({0.0f, 5.0f});
	rect.setOrigin({ 0.0f, rect.getSize().y / 2.0f });
	rect.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
	rect.setFillColor(sf::Color::Red);
	rect.setOutlineThickness(1.0f);
	rect.setOutlineColor(sf::Color::Black);

	sf::Font font;
	if (!font.openFromFile("../resources/fonts/prototype/prototype.ttf"))
	{
		std::cerr << "Error: Could not load file {../resources/fonts/prototype/prototype.ttf}" << std::endl;
	}

	std::stringstream sStream;
	sStream << "Vector 1: (" << rect.getSize().x << ", " << rect.getSize().y << ")";

	sf::Text vectorOne(font);
	vectorOne.setString(sStream.str());
	vectorOne.setOrigin(vectorOne.getGlobalBounds().size / 2.0f);
	vectorOne.setPosition({ window.getSize().x * 0.25f, 50.0f});
	vectorOne.setFillColor(sf::Color::Red);
	vectorOne.setOutlineThickness(1.0f);
	vectorOne.setOutlineColor(sf::Color::Black);

	sf::Text vectorTwo(font);
	vectorTwo.setString(sStream.str());
	vectorTwo.setOrigin(vectorTwo.getGlobalBounds().size / 2.0f);
	vectorTwo.setPosition({ window.getSize().x * 0.5f, 50.0f });
	vectorTwo.setFillColor(sf::Color::Red);
	vectorTwo.setOutlineThickness(1.0f);
	vectorTwo.setOutlineColor(sf::Color::Black);

	sf::Text vectorThree(font);
	vectorThree.setString(sStream.str());
	vectorThree.setOrigin(vectorThree.getGlobalBounds().size / 2.0f);
	vectorThree.setPosition({ window.getSize().x * 0.75f, 50.0f });
	vectorThree.setFillColor(sf::Color::Red);
	vectorThree.setOutlineThickness(1.0f);
	vectorThree.setOutlineColor(sf::Color::Black);

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

			sStream.str("");
			sStream.clear();
			sStream << "Vector 1: (" << direction.x << ", " << direction.y << ")";
			vectorOne.setString(sStream.str());
			vectorTwo.setString(sStream.str());
			vectorThree.setString(sStream.str());
		}

		window.clear(sf::Color::Cyan);
		window.draw(rect);
		window.draw(vectorOne);
		window.draw(vectorTwo);
		window.draw(vectorThree);
		window.display();
	}

	return 0;
}