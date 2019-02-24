#include "hill_climber.h"

void HillClimber::draw(
	sf::RenderTarget& target,
	sf::RenderStates states
) const {
	texture.loadFromImage(result);
	sprite.setTexture(texture);

	states.transform *= getTransform();
	target.draw(sprite, states);
}

double HillClimber::pixel_similatity(
	const sf::Color &a,
	const sf::Color &b
) const {

	double pixel_sim = 0;

	pixel_sim += abs(a.r - b.r);
	pixel_sim += abs(a.g - b.g);
	pixel_sim += abs(a.b - b.b);
	pixel_sim += abs(a.a - b.a);

	return 1 - (pixel_sim / (255 * 4.0f));
}

bool HillClimber::is_better(
	const sf::Rect<unsigned> &rect,
	const sf::Color color
) const {

	double current_similarity = 0;
	double new_similarity     = 0;

	for (unsigned y = rect.top; y != rect.top + rect.height; ++y) {
		for (unsigned x = rect.left; x != rect.left + rect.width; ++x) {

			current_similarity += pixel_similatity(
				original.getPixel(x, y),
				result.getPixel(x, y)
			);
			new_similarity += pixel_similatity(
				original.getPixel(x, y),
				color
			);
		}
	}

	// Normalize to [0-1]
	current_similarity = current_similarity / (rect.height * rect.width);
	new_similarity     = new_similarity     / (rect.height * rect.width);

	return (new_similarity > current_similarity);
}

sf::Rect<unsigned> HillClimber::create_random_rect() const {

	sf::Vector2u top_left(
		width_distribution(generator),
		height_distribution(generator)
	);
	sf::Vector2u bottom_right(
		width_distribution(generator),
		height_distribution(generator)
	);

	if (top_left.x > bottom_right.x) {
		std::swap(top_left.x, bottom_right.x);
	}
	if (top_left.y > bottom_right.y) {
		std::swap(top_left.y, bottom_right.y);
	}

	sf::Rect<unsigned> rect {
		top_left.x,
		top_left.y,
		bottom_right.x - top_left.x,
		bottom_right.y - top_left.y
	};

	if (rect.width * rect.height == 0) {
		return create_random_rect();
	} else {
		return rect;
	}
}

HillClimber::HillClimber(const std::string &path) {

	original.loadFromFile(path);

	width  = original.getSize().x;
	height = original.getSize().y;

	width_distribution  = std::uniform_int_distribution<unsigned>(0, width);
	height_distribution = std::uniform_int_distribution<unsigned>(0, height);
	color_distribution  = std::uniform_int_distribution<unsigned>(0, 255);

	result.create(width, height, sf::Color::Black);
}

void HillClimber::step() {

	auto rect = create_random_rect();

	sf::Color color(
		color_distribution(generator),
		color_distribution(generator),
		color_distribution(generator)
	);

	if (is_better(rect, color)) {

		for (unsigned y = rect.top; y != rect.top + rect.height; ++y) {
			for (unsigned x = rect.left; x != rect.left + rect.width; ++x) {
				result.setPixel(x, y, color);
			}
		}
	}
}

unsigned HillClimber::get_width() const {
	return width;
}

unsigned HillClimber::get_height() const {
	return height;
}
