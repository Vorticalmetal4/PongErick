#pragma once

struct VectorPositionBrick {
	int x;
	int y;
};

class Brick {
public:
	Brick();
	void setData(class Renderer* Rend, int XPosition, int YPosition, float Separation);
	void Draw(int raw);

	int getXPosition() { return Position.x; }
	int getYPosition() { return Position.y; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	void CheckCollition(class Ball* Ball);

private:
	VectorPositionBrick Position;
	int width;
	int height;
	Renderer* Rend;
	
};