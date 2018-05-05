#ifndef HILL_CLIMBER_H
#define HILL_CLIMBER_H

#include <SFML/Graphics.hpp>

class HillClimber : public sf::Drawable, public sf::Transformable {

	std::string path;
	sf::Image original;
	sf::Image result;
	unsigned width;
	unsigned height;
	mutable sf::Texture texture;
	mutable sf::Sprite sprite;

	double fitness = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		texture.loadFromImage(result);
		sprite.setTexture(texture);

		states.transform *= getTransform();
		target.draw(sprite, states);
	}

	double compare(const sf::Image &a, const sf::Image &b) {

		unsigned same = 0;

		for (unsigned y = 0; y != height; ++y) {
			for (unsigned x = 0; x != width; ++x) {

				if (a.getPixel(x, y) == b.getPixel(x, y)) {
					++same;
				}
			}
		}

		return same / (float) (width * height);
	}

public:

	HillClimber(const std::string &path) {

		original.loadFromFile(path);

		width = original.getSize().x;
		height = original.getSize().y;

		result.create(width, height, sf::Color::Black);
	}

	void step() {

		sf::Image tmp = result;

		unsigned x = rand() % width;
		unsigned y = rand() % height;

		tmp.setPixel(x, y, sf::Color::White);

		double cur_fitness = compare(tmp, original);

		if (cur_fitness > fitness) {
			result = tmp;
			fitness = cur_fitness;
		}
	}

	unsigned get_width() {
		return width;
	}

	unsigned get_height() {
		return height;
	}
};

#endif // HILL_CLIMBER_H
