#ifndef HILL_CLIMBER_H
#define HILL_CLIMBER_H

#include <random>
#include <SFML/Graphics.hpp>

class HillClimber : public sf::Drawable, public sf::Transformable {

	std::string path;
	sf::Image original;
	sf::Image result;
	unsigned width;
	unsigned height;
	mutable sf::Texture texture;
	mutable sf::Sprite sprite;

	mutable std::mt19937 generator;
	mutable std::uniform_int_distribution<unsigned> width_distribution;
	mutable std::uniform_int_distribution<unsigned> height_distribution;
	std::uniform_int_distribution<unsigned> color_distribution;

	double fitness = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool is_better(const sf::Rect<unsigned> &rect, const sf::Color color) const;

	double pixel_similatity(const sf::Color &a, const sf::Color &b) const;

	sf::Rect<unsigned> create_random_rect() const;

public:

	HillClimber(const std::string &path);

	void step();

	unsigned get_width() const;

	unsigned get_height() const;
};

#endif // HILL_CLIMBER_H
