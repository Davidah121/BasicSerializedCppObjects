#pragma once
#include "Serializable.h"

class AllDataType : public SerializedObject
{
public:
	AllDataType()
	{

	}
	~AllDataType()
	{

	}

	char b1 = 0;
	unsigned char b2 = 0;

	short b3 = 0;
	unsigned short b4 = 0;

	int b5 = 0;
	unsigned int b6 = 0;

	long b7 = 0;
	unsigned long b8 = 0;
	
	long long b9 = 0;
	unsigned long long b10 = 0;

	size_t a1 = 0;
	time_t a2 = 0;

	float f1 = 0;
	double f2 = 0;

	std::string s1 = "";
	
	SERIALIZE(b1);
	SERIALIZE(b2);
	SERIALIZE(b3);
	SERIALIZE(b4);
	SERIALIZE(b5);
	SERIALIZE(b6);
	SERIALIZE(b7);
	SERIALIZE(b8);
	SERIALIZE(b9);
	SERIALIZE(b10);

	SERIALIZE(a1);
	SERIALIZE(a2);

	SERIALIZE(f1);
	SERIALIZE(f2);

	SERIALIZE(s1);
private:

};