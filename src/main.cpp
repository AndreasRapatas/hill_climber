#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "./hill_climber.h"

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Invalid parameters!");
		printf("Usage: hill_climber \"/path/to/image.png\"\n");
		return 1;
	}

	HillClimber hillclimber(argv[1]);

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
