#define SDL_MAIN_HANDLED
#ifdef WIN32
#	include <SDL.h>
#	include <SDL_ttf.h>
#else
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_ttf.h>
#endif

#include <physfs.h>

#include <csaru-xapp-cpp/everything.hpp>

//======================================================================
TTF_Font * LoadDebugFont (const char * ttfPath) {
	if (!PHYSFS_exists(ttfPath)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No .ttf font at {%s} to use for debugging.\n", ttfPath);
		return nullptr;
	}

	SDL_RWops * rwOps = csaru::xapp::AllocRwOpsPhysFs(ttfPath, 'r');
	if (!rwOps) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL_RWops for PhysFS for application debug font, {%s}.\n", ttfPath);
		return nullptr;
	}

	TTF_Font * font = TTF_OpenFontRW(rwOps, 1 /* SDL_RWclose for me */, 28 /* font size */);
	if (!font) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ttf failed to load application debug font {%s}, {%s}.\n", ttfPath, TTF_GetError());
		return nullptr;
	}

	return font;
}

//======================================================================
int main (int argc, char * argv[]) {
	SDL_SetMainReady();

	csaru::xapp::Application app;
	if (!app.Init(argc, argv))
		return 1;

	PHYSFS_addToSearchPath("working-dir", 1);
	PHYSFS_addToSearchPath("working-dir/ubuntu-font-family-0.83.zip", 1);
	TTF_Font * debugFont = LoadDebugFont("ubuntu-font-family-0.83/UbuntuMono-R.ttf");
	if (!debugFont)
		return 1;
	app.SetFont("UbuntuMono-R", debugFont);
	app.SetDebugFont("UbuntuMono-R");

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

