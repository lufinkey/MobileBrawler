
#include "../SDL_internal.h"

#include "SDL_renderdriver.h"
#include "SDL_sysrender.h"

SDL_GLContext SDL_RendererGetGLContext(SDL_Renderer*renderer)
{
	return *((SDL_GLContext*)renderer->driverdata);
}
