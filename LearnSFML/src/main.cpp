#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML Works!");
	sf::CircleShape circle(100.f);
	circle.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		window.draw(circle);
		window.display();
	}

	return 0;
}