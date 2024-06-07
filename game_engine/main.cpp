// ===================================================================================================================================
// ||                                                         Aron Smith                                                            ||
// ||                                                  My Game Engine - main.cpp                                                    ||
// ||                                              CI517 - Game Engine Fundamentals                                                 ||
// ===================================================================================================================================

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "MyGame.h"
using namespace std;

//int main(int argc, char* args[])
//{
//	printf("Aron Smith - My Game Engine");
//	SDL_Window* gameWindow = NULL;
//	//Create window  
//	gameWindow = SDL_CreateWindow("Aron Smith - My Game Engine (CI517)", SDL_WINDOWPOS_UNDEFINED,
//		SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
//	if (gameWindow == NULL) printf(" Window Error %s\n", SDL_GetError());
//	SDL_Delay(5000);
//	SDL_Quit;
//	return 0;
//}

int main(int argc, char* argv[])
{
	try
	{
		MyGame game;
		game.runMainLoop();
	}
	catch (exception e)
	{
		cout << "error: " << endl;
	}

	return 0;
}

// ===================================================================================================================================
