#pragma once


class Paddle {
public:
	Paddle(int x, int y, int _Height, int _Velocity, int _Width);
	int getYPosition() { return yPosition; } 
	int getXPosition() { return xPosition; }
	int getVelocity() { return Velocity; }
	int getHeight() { return Height; }
	void Move(int yInc);
	bool CheckBorders(int yInc, int top, int down);
	bool CollitionWBall(class Ball* GameBall, int Side);


private:
	int xPosition;
	int yPosition;
	int Height;
	int Width;
	int Velocity;


};
