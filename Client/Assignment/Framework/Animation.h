// Animation Class
// Controls a single animation
// Stores a list of frames, animation speed, looping and lipped state.
// Returns current frame of animation based on time and updating.
// @author Paul Robertson

#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation();

	// Create animation
	void addFrame(sf::IntRect rect);
	void setFrameSpeed(float speed);
	int getSize();

	// update/reset animation
	void animate(float dt);
	void reset();

	// get current frame of animation
	sf::IntRect getCurrentFrame();

	// Animation controls
	float getFrameSpeed() { return animationSpeed; };
	void setFlipped(bool flip) { flipped = flip; };
	bool getFlipped() {	return flipped;	};
	void setLooping(bool loop) { isLooping = loop; };
	bool getLooping() { return isLooping; };
	void setPlaying(bool play) { isPlaying = play; };
	bool getPlaying() { return isPlaying; };
	void play(bool play) { isPlaying = true; };
	void stop();
	void pause() { isPlaying = false; };

protected:
	std::vector<sf::IntRect>frames;
	sf::IntRect frame;
	int currentFrame;
	float animationSpeed;
	bool flipped;
	bool isLooping;
	bool isPlaying;
	float elapsedTime;
};