#include "XMLHelper.h"

using namespace tinyxml2;

void XMLHelper::PrintVector3f(cstring name, liVector3f vec, XMLPrinter& printer) {
	printer.OpenElement(name);
	printer.PushAttribute("X", vec.x);
	printer.PushAttribute("Y", vec.y);
	printer.PushAttribute("Z", vec.z);
	printer.CloseElement();
}

void XMLHelper::PrintVector4f(cstring name, liVector4f vec, XMLPrinter& printer) {
	printer.OpenElement(name);
	printer.PushAttribute("X", vec.x);
	printer.PushAttribute("Y", vec.y);
	printer.PushAttribute("Z", vec.z);
	printer.PushAttribute("W", vec.w);
	printer.CloseElement();
}

int XMLHelper::ReadInt(XMLElement* element, cstring name) {
	return element->FirstChildElement(name)->FindAttribute("value")->IntValue();
}

int XMLHelper::ReadBool(XMLElement* element, cstring name) {
	return element->FirstChildElement(name)->FindAttribute("value")->BoolValue();
}

float XMLHelper::ReadFloat(XMLElement* element, cstring name) {
	return element->FirstChildElement(name)->FindAttribute("value")->FloatValue();
}

cstring XMLHelper::ReadString(XMLElement* element, cstring name) {
	return element->FirstChildElement(name)->FindAttribute("value")->Value();
}

liVector3f XMLHelper::ReadVec3(XMLElement* element, cstring name) {
	return liVector3f(element->FirstChildElement(name)->FindAttribute("X")->FloatValue(), element->FirstChildElement(name)->FindAttribute("Y")->FloatValue(), element->FirstChildElement(name)->FindAttribute("Z")->FloatValue());
}

liVector4f XMLHelper::ReadVec4(tinyxml2::XMLElement* element, cstring name) {
	return liVector4f(element->FirstChildElement(name)->FindAttribute("X")->FloatValue(), element->FirstChildElement(name)->FindAttribute("Y")->FloatValue(), element->FirstChildElement(name)->FindAttribute("Z")->FloatValue(), element->FirstChildElement(name)->FindAttribute("W")->FloatValue());
}