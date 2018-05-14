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

		double similarity = 0;

		for (unsigned y = 0; y != a.getSize().y; ++y) {
			for (unsigned x = 0; x != a.getSize().x; ++x) {

				double pixel_sim = 0;

				sf::Color ca(a.getPixel(x, y));
				sf::Color cb(b.getPixel(x, y));

				pixel_sim += abs(ca.r - cb.r);
				pixel_sim += abs(ca.g - cb.g);
				pixel_sim += abs(ca.b - cb.b);
				pixel_sim += abs(ca.a - cb.a);

				pixel_sim = 1 - (pixel_sim / (float) 1020);

				similarity += pixel_sim;
			}
		}

		return similarity / (float) a.getSize().x * (float) a.getSize().y;
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

		unsigned xl = rand() % width;
		unsigned xr = rand() % width;
		unsigned yt = rand() % height;
		unsigned yb = rand() % height;

		if (xl > xr) {
			std::swap(xl, xr);
		}
		if (yt > yb) {
			std::swap(yt, yb);
		}

		sf::Color color(
			rand() % 255,
			rand() % 255,
			rand() % 255,
			rand() % 255
		);

		for (unsigned y = yt; y != yb; ++y) {
			for (unsigned x = xl; x != xr; ++x) {
				tmp.setPixel(x, y, color);
			}
		}

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
