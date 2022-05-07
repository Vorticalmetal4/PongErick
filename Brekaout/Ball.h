#pragma once

struct VectorPositionB {
	int x;
	int y;
};

struct VectorVelocity {
	float x;
	float y;
};

class Ball {
public:
	Ball(class Renderer* Rend, class Player* Player1);
	int getXPosition() { return Position.x; }
	int getYPosition() { return Position.y; }
	void Update();

private:

	Renderer* Rend;
	Player* Player1;
	VectorPositionB Position;
	VectorVelocity Velocity;
	int height;
	int width;
};