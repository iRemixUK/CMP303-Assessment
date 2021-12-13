#pragma once
struct receivedPositionMessage {

	// The coordinates of the player within the game
	float x, y;

	// The time at which this message was sent.
	float time;
};