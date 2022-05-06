#pragma once

struct VectorPosition {
	int x;
	int y;
};

class Player {
public:
	Player(class Renderer* Rend);
	void Update();

private:
	Renderer* Rend;
	int PlayerVelocity;
	VectorPosition Position;
	int width;
	int height;
};