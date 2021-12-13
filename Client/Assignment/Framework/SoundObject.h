// Sound object
// Loads a sound file and stores related key.
// Key is used to find specific sounds for playback
// @author Paul Robertson

#pragma once
#include "SFML\Audio.hpp"

class SoundObject
{
public:
	SoundObject();
	~SoundObject();

	// Receives filepath and key name, loads sound file and stores alonside key
	void loadSound(std::string filename, std::string lname);

	// Sound and key variables. (shouldn't be public)
	sf::Sound sound;
	std::string name;
private:
	// Sound buffer must not leave scope or sound will be destroyed.
	sf::SoundBuffer* buffer;
	
};

