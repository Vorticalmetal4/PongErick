#include "Raycaster.h"
#include "CommonFiles/Renderer.h"

// NOTE(isaveg): What is this class for and how it is used
const float Pi = (float)3.141592;
const float Rad = Pi / 180;

Raycaster::Raycaster(Renderer* _Rend)
	:Rend(_Rend),
	Active(false),
	DeltaTime(0),
	D(0), 
	m(0)
{
	P1.x = P2.x = Center.x = -100;
	P1.y = P2.y = -100;
	P1.Rotation = P2.Rotation = Center.Rotation = 0;
	P1.Angle = P2.Angle = Center.Angle = 0;

}

Raycaster::~Raycaster()
{
}

void Raycaster::Update(int Velocity, Position* ParentP)
{
	DeltaTime = Rend->getDeltaTime();

	P1.x = P2.x = Center.x = ParentP->x;
	P1.y = P2.y = Center.y = ParentP->y;

	Center.Rotation = ParentP->Rotation;

	if(P1.x < Rend->getWindowWidth() / 2)
		D = Rend->getWindowWidth() - P1.x;
	else 
		D = P1.x,

	P1.x += cosf(Center.Rotation);
	P1.y -= sinf(Center.Rotation);
	P2.x += cosf(Center.Rotation) * D;
	P2.y -= sinf(Center.Rotation) * D;
	Center.x += cosf(Center.Rotation) * (D / 2.0f);
	Center.y -= sinf(Center.Rotation) * (D / 2.0f);

	Rend->DrawLine(&P1, &P2, 0, 0, 0, 0);
}

bool Raycaster::CheckCollision(float PlayerX, float PlayerY, float PlayerH)
{
	m = (P2.y - P1.y) / (P2.x - P1.x);

	if ((PlayerX > P1.x && PlayerX < P2.x) || (PlayerX < P1.x && PlayerX > P2.x))
		if ((PlayerY > P1.y && PlayerY < P2.y) || (PlayerY < P1.y && PlayerY > P2.y))
			if (abs(PlayerY - (m * PlayerX - m * Center.x + Center.y)) <= PlayerH)
				return true;
			else if (abs(PlayerY - (m * PlayerX - m * P1.x + P1.y)) <= PlayerH)
				return true;
			else if (abs(PlayerY - (m * PlayerX - m * P2.x + P2.y)) <= PlayerH)
				return true;
	
	return false;
}