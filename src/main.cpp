#include <SFML/Graphics.hpp>

#include "./hill_climber.h"

int main() {

	HillClimber hillclimber("../data/img.png");

	sf::RenderWindow window(
		sf::VideoMode(
			hillclimber.get_width(),
			hillclimber.get_height()
		),
		"Hill Climber"
	);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (
				event.type == sf::Event::Closed
				|| event.key.code == sf::Keyboard::Escape
			) {
				window.close();
			}
		}

		for (unsigned i = 0; i != 50; ++i) {
			hillclimber.step();
		}

		window.clear();
		window.draw(hillclimber);
		window.display();
	}

	return 0;
}
