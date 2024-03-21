#ifndef FRAMEWORK_XMLHELPER_H
#define FRAMEWORK_XMLHELPER_H
#include <lilib/EngineDefs.h>
#include <lilib/math/MathTypes.h>
#include <thirdparty/tinyxml2.h>

class XMLHelper {
private:
public:
	template<typename T>
	static void PrintGeneric(cstring name, T v, tinyxml2::XMLPrinter& printer);
	static void PrintVector3f(cstring name, liVector3f vec, tinyxml2::XMLPrinter& printer);
	static void PrintVector4f(cstring name, liVector4f vec, tinyxml2::XMLPrinter& printer);
	static int ReadInt(tinyxml2::XMLElement* element, cstring name);
	static int ReadBool(tinyxml2::XMLElement* element, cstring name);
	static float ReadFloat(tinyxml2::XMLElement* element, cstring name);
	static cstring ReadString(tinyxml2::XMLElement* element, cstring name);
	static liVector3f ReadVec3(tinyxml2::XMLElement* element, cstring name);
	static liVector4f ReadVec4(tinyxml2::XMLElement* element, cstring name);
};

template<typename T>
inline void XMLHelper::PrintGeneric(cstring name, T v, tinyxml2::XMLPrinter& printer)
{
	printer.OpenElement(name);
	printer.PushAttribute("value", v);
	printer.CloseElement();
}

#endif