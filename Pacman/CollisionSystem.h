#pragma once


struct Position
{
    float x;
    float y;
    int Angle;
    float Rotation;
};

struct Dimension
{
    float Width;
    float Height;
    float Hypotenuse;
};

class CollisionSystem
{
public:
    CollisionSystem();
    ~CollisionSystem();

    bool Square_Square(Position* Object1Pos, Position* Objec2Pos, Dimension* Object1Dimensions, Dimension* Object2Dimensions);
    bool Circle_Circle(Position* Object1Pos, Position* Object2Pos, float Object1Hypotenuse, float Object2Hypotenuse);
    bool Circle_Square(Position* CircleCenter, Position* SquarePoint, int CircleRadius, Dimension* SquareDimension);

    Position Aux;
};