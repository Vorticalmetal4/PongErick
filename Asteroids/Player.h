#pragma once

struct PlayerPosition
{
	int x;
	int y;
	int Angle;
	float Rotation;
};

struct PlayerVelocity
{
	int x;
	int y;
};

class Player
{
public:
	Player(class Renderer* _Rend);
	~Player();
	void Update();
	void Rotation();

private:
	Renderer* Rend;
	PlayerPosition FirstPoint;
	PlayerPosition SecondPoint;
	PlayerPosition ThirdPoint;
	PlayerPosition Center;
	PlayerVelocity Velocity;
	int Width;
	int Height;
	int HWidth;
	int HHeight;
	float H;
	float DeltaTime;
	int Velocity;
	

};