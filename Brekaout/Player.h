#pragma once

struct VectorPosition {
	int x;
	int y;
};

class Player {
public:
	Player(class Renderer* Rend);
	void Update();
	int getXPosition() { return Position.x; }
	int getYPosition() { return Position.y; }
	int getWidth() { return width; }
	int getHeight() { return height; }

private:

	Renderer* Rend;
	int PlayerVelocity;
	VectorPosition Position;
	int width;
	int height;

};