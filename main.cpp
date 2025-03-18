
#include "GameEngine.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char* argv[]) {

	
	GameEngine *game = new GameEngine();

	delete game;
	return 0;
}


