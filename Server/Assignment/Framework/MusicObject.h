// Music object class
// Stores the filename/path and key for a music file.
// Music files are not loaded into memory due to size, but are streamed from storage
// @author Paul Robertson

#pragma once
#include "SFML\Audio.hpp"

class MusicObject
{
public:
	MusicObject();
	~MusicObject();

	// Store the music file path and key.
	void setMusic(std::string lfilename, std::string lname);

	// Music variables (shouldn't be public)
	std::string filename;
	std::string name;
};

