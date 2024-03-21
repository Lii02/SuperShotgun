#ifndef RENDERER_SPRITE_H
#define RENDERER_SPRITE_H
#include <lilib/EngineDefs.h>
#include "Texture2D.h"

extern uint32_t sprite_vao, sprite_vbo, sprite_ibo, sprite_tbo;

class Sprite {
private:
	Texture2D* image;
public:
	static void InitializeSpriteGraphics();
	static void ShutdownSpriteGraphics();

	Sprite() {}
	Sprite(Texture2D* image);
	~Sprite();
	
	void Draw();
	Texture2D* GetImage();
	void SetImage(Texture2D* image);
};

#endif