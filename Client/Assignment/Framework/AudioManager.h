// Audio Manager Class
// Manages storage and playback of multiple sound and music objects.
// Maintains lists of Sound and Music for playback in game
// @author Paul Robertson

#pragma once

#include "SoundObject.h"
#include "MusicObject.h"
#include "SFML\Audio.hpp"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	
	// Add sound object, provide file path and key string
	void addSound(std::string filename, std::string lname);
	// Plays sound based on key string provided (if sound exists).
	void playSoundbyName(std::string lname);
	// Stops playing all sounds (multiple sfx's can be played simultaneously
	void stopAllSounds();
	// Returns the sound object (based on key string). Can be useful for tracking play state, looping, volume etc.
	sf::Sound* getSound(std::string lname);

	// Add music object, provide file path and key string.
	void addMusic(std::string filename, std::string lname);
	// Play/stream music based on key string provided (if music exists).
	void playMusicbyName(std::string lname);
	// Stop music.
	void stopAllMusic();
	// Return pointer to music object. Useful for controlling looping, play state, volume etc.
	sf::Music* getMusic();

private:
	// List of sounds
	std::vector<SoundObject> sounds;
	// List of Musics
	std::vector<MusicObject> musics;
	// Single Music object as the stream cannot be copied.
	sf::Music music;
	// Re-useable sound object
	SoundObject s;
};

