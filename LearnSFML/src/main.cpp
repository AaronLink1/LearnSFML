#include <SFML/Graphics.hpp>
#include <cmath>
#include <numbers>
#include <iostream>
#include <sstream>

//Currently basing the location of the circle off of the rectangle. Technically the rectangle should be based off the location of the circle.

constexpr double RAD_TO_DEG (180.0 / std::numbers::pi);

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1980, 1080 }), "SFML Learning Vectors");
	window.setVerticalSyncEnabled(true);

	bool moveVertex = false;

	sf::CircleShape vertex(5.0f);
	vertex.setOrigin(vertex.getGeometricCenter());
	vertex.setPosition({ 1300.0f, 300.0f });
	vertex.setFillColor(sf::Color::Green);
	vertex.setOutlineThickness(1.0f);
	vertex.setOutlineColor(sf::Color::Black);

	sf::Vector2f initDirection = { vertex.getPosition().x - window.getSize().x / 2.0f, vertex.getPosition().y - window.getSize().y / 2.0f };
	sf::RectangleShape vector({std::hypotf(initDirection.x, initDirection.y), 5.0f});
	vector.setRotation(sf::degrees(std::atan2(initDirection.y, initDirection.x) * RAD_TO_DEG));
	vector.setOrigin({ 0.0f, vector.getSize().y / 2.0f });
	vector.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
	vector.setFillColor(sf::Color::Red);
	vector.setOutlineThickness(1.0f);
	vector.setOutlineColor(sf::Color::Black);

	sf::Font font;
	if (!font.openFromFile("../resources/fonts/prototype/prototype.ttf"))
	{
		std::cerr << "Error: Could not load file {../resources/fonts/prototype/prototype.ttf}" << std::endl;
	}

	std::stringstream sStream;
	sStream << "Vector 1: (" << std::cos(vector.getRotation().asRadians()) * vector.getSize().x << ", " 
			<< std::sin(vector.getRotation().asRadians()) * vector.getSize().x << ")";

	

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
			else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (vertex.getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition(window) }))
					moveVertex = true;
			}
			else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
			{
				moveVertex = false;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (moveVertex)
			{
				vertex.setPosition(sf::Vector2f{ sf::Mouse::getPosition(window) });

				sf::Vector2f direction = { vertex.getPosition().x - window.getSize().x / 2.0f, vertex.getPosition().y - window.getSize().y / 2.0f };
				vector.setSize({ std::hypotf(direction.x, direction.y), 5.0f });
				vector.setRotation(sf::degrees(std::atan2(direction.y, direction.x) * RAD_TO_DEG));

				sStream.str("");
				sStream.clear();
				sStream << "Vector 1: (" << std::cos(vector.getRotation().asRadians()) * vector.getSize().x << ", "
					<< std::sin(vector.getRotation().asRadians()) * vector.getSize().x << ")";
				vectorOne.setString(sStream.str());
				vectorTwo.setString(sStream.str());
				vectorThree.setString(sStream.str());
			}
		}

		window.clear(sf::Color::White);
		window.draw(vector);
		window.draw(vertex);
		window.draw(vectorOne);
		window.draw(vectorTwo);
		window.draw(vectorThree);
		window.display();
	}

	return 0;
}