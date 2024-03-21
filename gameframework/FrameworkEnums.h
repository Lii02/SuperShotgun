#ifndef FRAMEWORK_ENUMS_H
#define FRAMEWORK_ENUMS_H

enum liActorFlag : int {
	FLAG_GUI = 0x1,
	FLAG_2D = 0x2,
	FLAG_3D = 0x3,
	FLAG_CAMERA = 0x4,
};

enum liActorType : int {
	TYPE_ACTOR = 0x1,
	TYPE_ACTOR3D = 0x2,
	TYPE_CAMERA = 0x3,
	TYPE_LIGHT = 0x4,
	TYPE_ACTOR2D = 0x5,
	TYPE_LABEL = 0x6,
	TYPE_GUITEXTURE = 0x7,
	TYPE_GUIBUTTON = 0x8,
};

#endif