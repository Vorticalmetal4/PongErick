#include "Renderer.h"
#include "CollisionSystem.h"
#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "Unity/unity.h"

void Test_MouthAngles()
{
    int _Angle = 0;
    int _FirstMouthAngle;
    int _MouthSize = 30;

    if (_Angle > 0)
        _FirstMouthAngle = _Angle - _MouthSize;

    else
        _FirstMouthAngle = 360 - _MouthSize;

    TEST_ASSERT_MESSAGE(330 == _FirstMouthAngle, "The Mouth Angle isn't zero");
}

int main()
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

    Renderer Rend;
    CollisionSystem CollisionDetector;
    Player MainPlayer(&Rend);

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
        ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
        ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
        ConFile.GetInteger("Window", "Width", 1080),
        ConFile.GetInteger("Window", "Height", 700),
        ConFile.GetInteger("Window", "Flags", 0),
        ConFile.GetString("Window", "Font", "Error"));

    if (success)
    {
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();

            MainPlayer.Update();

            Rend.GenerateOutput();
        }
    }

    UNITY_BEGIN();

    RUN_TEST(Test_MouthAngles);

    UNITY_END();

	return 0;
}