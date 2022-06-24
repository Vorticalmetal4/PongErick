#pragma once

struct PlayerPosition
{
	int x;
	int y;
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

private:
	Renderer* Rend;
	PlayerPosition FirstPoint;
	PlayerPosition SecondPoint;
	PlayerPosition ThirdPoint;
	PlayerVelocity Velocity;
	int Width;
	int Height;

};