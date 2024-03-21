#ifndef TTF_H
#define TTF_H
#include <lilib/EngineDefs.h>
#include <gameframework/File.h>
#include <gameframework/Asset.h>
#include <lilib/Dictionary.h>
#include <lilib/math/MathTypes.h>
#include <gameframework/FrameworkStructs.h>

class liTTF : public liAsset {
private:
	liDictionary<char, character_data_t> glyphs;
	float font_size;
public:
	liTTF(liFile* file, float font_size);
	~liTTF();
	FontData GetFontData();
	float GetFontSize() const;

	static liTTF* Load(liFile* file, float font_size = 36);
};

#endif