#pragma once

struct VectorPositionB 
{
	int x;
	int y;
};

struct VectorVelocity 
{
	float x;
	float y;
};

class Ball 
{
public:
	Ball(class Renderer* _Rend, class Player* _Player1);
	int getXPosition() { return Position.x; }
	int getYPosition() { return Position.y; }
	int getXVelocity() { return Velocity.x; }
	int getHeight() { return height; }
	int getWidth() { return width; }
	void ChangeXDirection() { Velocity.x *= -1; }
	void ChangeYDirection() { Velocity.y *= -1; }
	void SetCollitionWPlayer() { CollWPlayer = false; }
	void IncXVelocity();
	void IncYVelocity();
	bool Update(bool Pause);

private:

	Renderer* Rend = nullptr; 
	Player* Player1 = nullptr;
	VectorPositionB Position;
	VectorPositionB InitialPosition;
	VectorVelocity Velocity;
	int height;
	int width;
	int InitialVelocity;
	int MaxVelocity;
	int VelocityIncrease;
	bool CollWPlayer;

	float DeltaTime;
	float XInc;
	float YInc;
	float PlayerXPosition;
};