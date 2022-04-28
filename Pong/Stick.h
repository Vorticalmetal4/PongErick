#pragma once


class Stick {
public:
	Stick(int x, int y, int height, int Velocity, int Width);
	int getYPosition();
	int getXPosition();
	int getHeight();
	int getVelocity();
	void MoveYPosition(int yInc);
	bool CheckBorders(int yInc, int top, int down);
	bool CollitionWBall(class Ball* GameBall, int Side);


private:
	int xPosition;
	int yPosition;
	int height;
	int Width;
	int Velocity;


};
