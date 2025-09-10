#include <SFML/Graphics.hpp>
#include <cmath>
#include <numbers>
#include <iostream>
#include <sstream>
#include <vector>

constexpr double RAD_TO_DEG (180.0 / std::numbers::pi);
struct VertexVector { bool move; int index; };

constexpr int numVertex = 5;
constexpr int numVectors = numVertex;

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1980, 1080 }), "SFML Learning Vectors");
	window.setVerticalSyncEnabled(true);

	VertexVector moveVertex{ false, 0 };

	std::vector<sf::CircleShape> vertexes;
	for (int i = 0; i < numVertex; i++)
	{
		sf::CircleShape vertex(5.0f);
		vertex.setOrigin(vertex.getGeometricCenter());
		vertex.setPosition({ (i + 1) * 200.0f, (i % 2 + 1) * 200.0f });
		vertex.setFillColor(sf::Color::Green);
		vertex.setOutlineThickness(1.0f);
		vertex.setOutlineColor(sf::Color::Black);
		vertexes.push_back(vertex);
	}

	std::vector<sf::RectangleShape> vectors;
	for (int i = 0; i < numVectors; i++)
	{
		sf::Vector2f initDirection = { 0.0f, 0.0f };
		if (i + 1 == numVectors)
			initDirection = vertexes[0].getPosition() - vertexes[i].getPosition();
		else
			initDirection = vertexes[i + 1].getPosition() - vertexes[i].getPosition();

		sf::RectangleShape vector({ std::hypotf(initDirection.x, initDirection.y), 5.0f });
		vector.setRotation(sf::degrees(std::atan2(initDirection.y, initDirection.x) * RAD_TO_DEG));
		vector.setOrigin({ 0.0f, vector.getSize().y / 2.0f });
		vector.setPosition(vertexes[i].getPosition());
		vector.setFillColor(sf::Color::Red);
		vector.setOutlineThickness(1.0f);
		vector.setOutlineColor(sf::Color::Black);
		vectors.push_back(vector);
	}
	
	sf::Font font;
	if (!font.openFromFile("../resources/fonts/prototype/prototype.ttf"))
	{
		std::cerr << "Error: Could not load file {../resources/fonts/prototype/prototype.ttf}" << std::endl;
	}

	std::vector<sf::Text> vectorText;
	for (int i = 0; i < numVectors; i++)
	{
		sf::Text vectorTemp(font);
		//vectorTemp.setOrigin(vectorTemp.getGlobalBounds().size / 2.0f);
		vectorTemp.setPosition({ window.getSize().x * (1.0f / (numVectors + 1)) * (i + 1), 50.0f });
		vectorTemp.setFillColor(sf::Color::Red);
		vectorTemp.setOutlineThickness(1.0f);
		vectorTemp.setOutlineColor(sf::Color::Black);
		vectorText.push_back(vectorTemp);
	}

	std::stringstream sStream;
	for (int i = 0; i < numVectors; i++)
	{
		sStream.str("");
		sStream.clear();
		sf::Vector2f direction = { 0.0f, 0.0f };
		if (i + 1 == numVectors)
			direction = vertexes[0].getPosition() - vertexes[i].getPosition();
		else 
			direction = vertexes[i + 1].getPosition() - vertexes[i].getPosition();

		sStream << "Vector " << i << ": (" << direction.x << ", " << direction.y << ")";
		vectorText[i].setString(sStream.str());
		vectorText[i].setOrigin(vectorText[i].getGlobalBounds().size / 2.0f);
	}

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
				for (int i = 0; i < numVertex; i++)
					if (vertexes[i].getGlobalBounds().contains(sf::Vector2f{sf::Mouse::getPosition(window)}))
					{
						moveVertex.move = true;
						moveVertex.index = i;
					}
			}
			else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
			{
				moveVertex.move = false;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (moveVertex.move)
			{
				vertexes[moveVertex.index].setPosition(sf::Vector2f{sf::Mouse::getPosition(window)});

				if (moveVertex.index == numVertex - 1)
				{
					sf::Vector2f direction = vertexes[moveVertex.index].getPosition() - vertexes[moveVertex.index - 1].getPosition();
					vectors[moveVertex.index - 1].setSize({ std::hypotf(direction.x, direction.y), 5.0f });
					vectors[moveVertex.index - 1].setRotation(sf::degrees(std::atan2(direction.y, direction.x) * RAD_TO_DEG));

					direction = vertexes[0].getPosition() - vertexes[moveVertex.index].getPosition();
					vectors[moveVertex.index].setPosition(vertexes[moveVertex.index].getPosition());
					vectors[moveVertex.index].setSize({ std::hypotf(direction.x, direction.y), 5.0f });
					vectors[moveVertex.index].setRotation(sf::degrees(std::atan2(direction.y, direction.x)* RAD_TO_DEG));
				}
				else if (moveVertex.index > 0)
				{
					sf::Vector2f direction = vertexes[moveVertex.index].getPosition() - vertexes[moveVertex.index - 1].getPosition();
					vectors[moveVertex.index - 1].setSize({ std::hypotf(direction.x, direction.y), 5.0f });
					vectors[moveVertex.index - 1].setRotation(sf::degrees(std::atan2(direction.y, direction.x)* RAD_TO_DEG));

					direction = vertexes[moveVertex.index + 1].getPosition() - vertexes[moveVertex.index].getPosition();
					vectors[moveVertex.index].setPosition(vertexes[moveVertex.index].getPosition());
					vectors[moveVertex.index].setSize({ std::hypotf(direction.x, direction.y), 5.0f });
					vectors[moveVertex.index].setRotation(sf::degrees(std::atan2(direction.y, direction.x)* RAD_TO_DEG));
				}
				else
				{
					sf::Vector2f direction = vertexes[moveVertex.index + 1].getPosition() - vertexes[moveVertex.index].getPosition();
					vectors[moveVertex.index].setPosition(vertexes[moveVertex.index].getPosition());
					vectors[moveVertex.index].setSize({ std::hypotf(direction.x, direction.y) , 5.0f });
					vectors[moveVertex.index].setRotation(sf::degrees(std::atan2(direction.y, direction.x) * RAD_TO_DEG));

					direction = vertexes[moveVertex.index].getPosition() - vertexes[numVertex - 1].getPosition();
					vectors[numVectors - 1].setSize({ std::hypotf(direction.x, direction.y), 5.0f });
					vectors[numVectors - 1].setRotation(sf::degrees(std::atan2(direction.y, direction.x)* RAD_TO_DEG));
				}

				for (int i = 0; i < numVectors; i++)
				{
					sStream.str("");
					sStream.clear();
					sf::Vector2f direction = { 0.0f, 0.0f };
					if (i + 1 == numVectors)
						direction = vertexes[0].getPosition() - vertexes[i].getPosition();
					else
						direction = vertexes[i + 1].getPosition() - vertexes[i].getPosition();

					sStream << "Vector " << i << ": (" << direction.x << ", " << direction.y << ")";
					vectorText[i].setString(sStream.str());
				}
			}
		}

		window.clear(sf::Color::White);
		for (sf::RectangleShape vector : vectors)
			window.draw(vector);
		for (sf::CircleShape vertex : vertexes)
			window.draw(vertex);
		for (sf::Text text : vectorText)
			window.draw(text);
		window.display();
	}

	return 0;
}