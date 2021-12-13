#include "SoundObject.h"

SoundObject::SoundObject()
{
	buffer = nullptr;
}

SoundObject::~SoundObject()
{

}

// Loads sound into memory and can be identified by key (name).
// Receives filepath and key name, loads sound file and stores alonside key
void SoundObject::loadSound(std::string filename, std::string lname)
{
	buffer = new sf::SoundBuffer();
	buffer->loadFromFile(filename);
	sound.setBuffer(*buffer);
	name = lname;
}
