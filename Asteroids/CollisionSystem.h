#pragma once

// NOTE(isaveg): Asteroid, Player, EnemyShip all use the collission system, what Object pattern reminds your? How can you generalize for all cases

struct Position
{
    float x;
    float y;
    int Angle;
    float Rotation;
};

struct Dimension
{
    int Width;
    int Height;
    float Hypotenuse;
};

class CollisionSystem
{
public:
    CollisionSystem();
    ~CollisionSystem();

    // NOTE(isaveg): Makes more sense as static functions
    bool Square_Square(Position* Object1Pos, Position* Objec2Pos, Dimension* Object1Dimensions, Dimension* Object2Dimensions); 
    bool Circle_Circle(Position* Object1Pos, Position* Object2Pos, float Object1Hypotenuse, float Object2Hypotenuse);

};
