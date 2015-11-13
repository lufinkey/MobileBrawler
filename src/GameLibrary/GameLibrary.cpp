
#include "GameLibrary.h"

int main(int argc, char *argv[]);

#ifdef main
#undef main
#endif

#include <SDL_main.h>

int main(int argc, char *argv[])
{
	return GameLibrary_main(argc, argv);
}

#if _MSC_VER >= 1400
	FILE _iob[] = { *stdin, *stdout, *stderr };

	extern "C" FILE * __cdecl __iob_func(void)
	{
		return _iob;
	}
#endif
