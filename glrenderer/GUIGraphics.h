#ifndef RENDERER_GUIGRAPHICS_H
#define RENDERER_GUIGRAPHICS_H
#include <lilib/EngineDefs.h>
#include "Texture2D.h"

extern uint32_t gui_vao, gui_vbo, gui_ibo, gui_tbo;

class GUIGraphics {
public:
	static void Initialize();
	static void Shutdown();
	static void Draw(Texture2D* image);
};

#endif