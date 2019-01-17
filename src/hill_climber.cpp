#include "hill_climber.h"
#include <iostream>

void HillClimber::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	texture.loadFromImage(result);
	sprite.setTexture(texture);

	states.transform *= getTransform();
	target.draw(sprite, states);
}

double HillClimber::compare(const sf::Image &a, const sf::Image &b) const {

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


HillClimber::HillClimber(const std::string &path) {

	original.loadFromFile(path);

	width = original.getSize().x;
	height = original.getSize().y;

	result.create(width, height, sf::Color::Black);
}

void HillClimber::step() {

	sf::Image tmp = result;

	sf::Vector2u top_left(rand() % width, rand() % height);
	sf::Vector2u bottom_right(rand() % width, rand() % height);

	if (top_left.x > bottom_right.x) {
		std::swap(top_left.x, bottom_right.x);
	}
	if (top_left.y > bottom_right.y) {
		std::swap(top_left.y, bottom_right.y);
	}

	sf::Color color(
		rand() % 255,
		rand() % 255,
		rand() % 255
	);

	for (unsigned y = top_left.y; y != bottom_right.y; ++y) {
		for (unsigned x = top_left.x; x != bottom_right.x; ++x) {
			tmp.setPixel(x, y, color);
		}
	}

	double cur_fitness = compare(tmp, original);

	if (cur_fitness > fitness) {
		result = tmp;
		fitness = cur_fitness;
	}
}

unsigned HillClimber::get_width() const {
	return width;
}

unsigned HillClimber::get_height() const {
	return height;
}
