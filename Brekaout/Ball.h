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
	int getXVelocity() { return Velocity.x; }
	int getHeight() { return height; }
	int getWidth() { return width; }
	void setXVelocity(int x) { Velocity.x *= x; }
	void setYVelocity(int y) { Velocity.y *= y; }
	void Update();

private:

	Renderer* Rend;
	Player* Player1;
	VectorPositionB Position;
	VectorVelocity Velocity;
	int height;
	int width;
};