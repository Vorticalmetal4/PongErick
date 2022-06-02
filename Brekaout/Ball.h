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
	Ball(class Renderer* Rend, class Player* Player1, class HUD* Hud);
	int getXPosition() { return Position.x; }
	int getYPosition() { return Position.y; }
	int getXVelocity() { return Velocity.x; }
	int getHeight() { return height; }
	int getWidth() { return width; }
	void ChangeXDirection() { Velocity.x *= -1; }
	void ChangeYDirection() { Velocity.y *= -1; }
	void IncXVelocity();
	void IncYVelocity();
	void Update();

private:

	Renderer* Rend;
	Player* Player1;
	HUD* Hud;
	VectorPositionB Position;
	VectorPositionB InitialPosition;
	VectorVelocity Velocity;
	int height;
	int width;
	int InitialVelocity;
	int MaxVelocity;
	int VelocityIncrease;
};