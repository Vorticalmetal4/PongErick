#pragma once

struct VectorPositionRay {
	int x;
	int y;
};

class Ray {
public:
	Ray(int X, int Y, class Renderer* Rend);
	int getPositionX() { return Position.x; }
	int getPositionY() { return Position.y; }
	int getWidth() { return Width; }
	int getHeigth() { return Height; }
	bool CheckCollition(class Brick* ActualBrick, int DeltaTime);
	

private:
	VectorPositionRay Position;
	Renderer* Rend;
	int Width;
	int Height;
	int Velocity;
};