#pragma once

struct VectorPositionBrick {
	int x;
	int y;
};

class Brick {
public:
	Brick();
	~Brick();
	void setData(class Renderer* Rend, int XPosition, int YPosition, float Separation);
	void Draw(int raw);

	int getXPosition() { return Position.x; }
	int getYPosition() { return Position.y; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	bool getActive() { return Active; }
	bool CheckCollition(class Ball* Ball);
	void setYPosition(int Y) {Position.y = Y; }

private:
	VectorPositionBrick Position;
	int width;
	int height;
	Renderer* Rend;
	bool Active;
	
};