#pragma once // CPP: Esto es valido para la  mayoria de los compiladores modernos, aunque siempre estar atento que no es la unica forma de evitar multiple inclusion

class Ball {
public:
	Ball(int x, int y, int xVelocity, int yVelocity, int Size);
	int getXPosition();
	int getYPosition();
	int getXVelocity();
	int getYVelocity();
	int getSize();
	void Move(int xinc, int yinc);
	void GameStarted();
	void setXVelocity();
	void setYVelocity();
	void WallCollition(int Height, int Width, class Score* Sc);

private:
	int xPosition;
	int yPosition;
	int xVelocity;
	int yVelocity;
	int Size;
};
