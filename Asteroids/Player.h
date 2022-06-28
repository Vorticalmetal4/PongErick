#pragma once

struct PlayerPosition
{
	double x;
	double y;
	int Angle;
	double Rotation;
};

class Player
{
public:
	Player(class Renderer* _Rend);
	~Player();
	void Update();
	void MovePoints(bool Rotation);

private:
	Renderer* Rend;
	PlayerPosition FirstPoint;
	PlayerPosition SecondPoint;
	PlayerPosition ThirdPoint;
	PlayerPosition Center;
	int Width;
	int Height;
	double H;
	float DeltaTime;
	int Velocity;
	int MaxVelocity;
	int IncVelocity;
	int DecVelocity;
	int RotationVelocity;

};