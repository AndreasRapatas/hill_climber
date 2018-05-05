#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

#include "./hill_climber.h"

using namespace std;
using namespace sf;

int main() {

	HillClimber hillclimber("../data/img.png");

	RenderWindow window(VideoMode(hillclimber.get_width(), hillclimber.get_height()), "Hill Climber");
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (
				event.type == Event::Closed
				|| event.key.code == Keyboard::Escape
			) {
				window.close();
			}
		}

		window.clear();
		hillclimber.step();
		window.draw(hillclimber);
		window.display();
	}

	return 0;
}
