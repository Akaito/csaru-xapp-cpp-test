#ifdef WIN32
#	include <SDL.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#endif

#include <csaru-xapp-cpp/everything.hpp>

int main (int argc, char * argv[]) {
	argc; argv;

	csaru::xapp::Window winA;
	csaru::xapp::Window winB;

	winA.Init("Win A", 1366, 768);
	winB.Init("Win B",  640, 480);

	SDL_Delay(2000);

	return 0;
}

