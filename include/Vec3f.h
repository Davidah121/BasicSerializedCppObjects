#pragma once
#include"Serializable.h"

class Vec3f: public SerializedObject
{
public:
	Vec3f();
	~Vec3f();

	double x = 0;
	double y = 0;
	double z = 0;

	SERIALIZE(x);
	SERIALIZE(y);
	SERIALIZE(z);
	
private:

};