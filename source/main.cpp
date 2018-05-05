#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {

	RenderWindow window(VideoMode(200, 100), "Hill Climber");
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
		window.display();
	}

	return 0;
}
