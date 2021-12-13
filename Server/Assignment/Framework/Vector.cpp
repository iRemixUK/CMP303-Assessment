#include "Vector.h"

// Returns a normalised vector
sf::Vector2f Vector::normalise(const sf::Vector2f &source)
{
	float length = (float)sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

// Returns the Vector magnitude
float Vector::magnitude(sf::Vector2f vec)
{
	return (float)sqrt((vec.x*vec.x) + (vec.y*vec.y));
}




