#include "Inih/cpp/INIReader.h"
#include "Renderer.h"
#include "Player.h"


int main()
{
    INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

	Renderer Rend;
    Player MainPlayer = Player(&Rend);

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
                                   ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
                                   ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
                                   ConFile.GetInteger("Window", "Width", 1080),
                                   ConFile.GetInteger("Window", "Height", 700),
                                   ConFile.GetInteger("Window", "Flags", 0),
                                   ConFile.GetString("Window", "Font", "Error"));

    if(success)
    {
        while(Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();


            MainPlayer.Update();
            Rend.GenerateOutput();
        }
    }
}