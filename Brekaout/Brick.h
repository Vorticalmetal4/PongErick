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

private:
	VectorPositionBrick Position;
	int width;
	int height;
	Renderer* Rend;
	
};