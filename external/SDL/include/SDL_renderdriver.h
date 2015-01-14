
#ifndef _SDL_renderdriver_h
#define _SDL_renderdriver_h

#include "SDL_opengl.h"
#include "SDL_render.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

extern DECLSPEC SDL_GLContext SDLCALL SDL_RendererGetGLContext(SDL_Renderer*renderer);

#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* _SDL_renderdriver_h */
