#ifndef RENDERER_FONTGRAPHICS_H
#define RENDERER_FONTGRAPHICS_H
#include <lilib/EngineDefs.h>
#include <glrenderer/Texture2D.h>
#include <gameframework/FrameworkStructs.h>
#include <lilib/LiString.h>
#include <lilib/Dictionary.h>

extern uint32_t font_vao, font_vbo;

class FontGraphics {
public:
	static void Initialize();
	static void Shutdown();
	static float CalculateWidth(FontData data, liString text, int kerning);
	static void DrawString(FontData data, liString text, int kerning);
};

#endif