#pragma once
#include"Serializable.h"
#include"Vec3f.h"
#include"TestTemplate.h"

class SpecialString : public SerializedObject
{
public:
	SpecialString(std::string s1, std::string s2);
	~SpecialString();

private:
	std::string myString;
	std::string myString2;
	Vec3f pos;
	TestTemplate<Vec3f> templatePos = TestTemplate(Vec3f());

	SERIALIZE(myString);
	SERIALIZE_TYPENAME(myString2, "std::string");
	SERIALIZE(pos);
	SERIALIZE(templatePos);

};