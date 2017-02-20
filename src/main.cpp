#define SDL_MAIN_HANDLED
#ifdef WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif

#include <csaru-xapp-cpp/everything.hpp>

int main (int argc, char * argv[]) {
	SDL_SetMainReady();
	argc; argv;

	csaru::xapp::Application app;
	if (!app.Init())
		return 1;

	csaru::xapp::Window winA;
	csaru::xapp::Window winB;

	winA.Init("Win A", 1366, 768);
	SDL_SetRenderDrawColor(winA.SdlRenderer(), 0x20, 0x20, 0x20, 0xFF);
	app.AddWindow(&winA);

	winB.Init("Win B",  640, 480);
	SDL_SetRenderDrawColor(winB.SdlRenderer(), 0xDF, 0xDF, 0xDF, 0xFF);
	app.AddWindow(&winB);

	winA.DebugPrint("Hello");
	winB.DebugPrint("World");

	while (app.HasOpenWindows()) {
		app.PollEvents();
		if (app.IsQuitting())
			break;

		winA.Clear();
		winB.Clear();

		winA.Render();
		winB.Render();
		SDL_Delay(16); // 16 milliseconds
	}

	return 0;
}

