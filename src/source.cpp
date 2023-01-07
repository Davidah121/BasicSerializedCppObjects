#include<iostream>
#include<fstream>
#include"Serializable.h"
#include"Vec3f.h"
#include"SpecialString.h"
#include"AllDataType.h"

#define TTS(s) typeid(s).name()
#define TTI(s) typeid(s)

void test1()
{
	int v1 = 1;
	int v2 = 4;
	short v3 = 8;
	char v4 = 12;
	
	SERIALIZE_NOCLASS(v1);
	SERIALIZE_NOCLASS(v2);
	SERIALIZE_NOCLASS(v3);
	SERIALIZE_NOCLASS(v4);
	

	SerializedData* p1 = (SerializedData*)&SERIALIZED__v1__;
	SerializedData* p2 = (SerializedData*)&SERIALIZED__v2__;
	SerializedData* p3 = (SerializedData*)&SERIALIZED__v3__;
	SerializedData* p4 = (SerializedData*)&SERIALIZED__v4__;

	printf("%p, %p, %p, %p\n", p1, p2, p3, p4);
	printf("%p, %p, %p, %p\n", p1->getData(), p2->getData(), p3->getData(), p4->getData());
	printf("%d, %d, %d, %d\n", *((int*)p1->getData()), *((int*)p2->getData()), *((int*)p3->getData()), *((int*)p4->getData()));
	printf("%s, %s, %s, %s\n", p1->getName().c_str(), p2->getName().c_str(), p3->getName().c_str(), p4->getName().c_str());
}

void test2()
{
	Vec3f v = Vec3f();
	
	//verification stuff
	printf("Number of Serialized Variables: %llu\n", v.getVariables().size());

	if(v.getVariables().size() == 3)
	{	
		printf("Serialized Version:\n");
		for(SerializedData* temp : v.getVariables())
		{
			printf("\t%s %s = %p\n", temp->getType().c_str(), temp->getName().c_str(), temp->getData());
		}
		printf("\n");
		printf("Actual Version:\n");
		printf("\tdouble x = %p\n", &v.x);
		printf("\tdouble y = %p\n", &v.y);
		printf("\tdouble z = %p\n", &v.z);
	}


}

void test3()
{
	std::string k = "";
	std::string v = TTS(k);
	
	printf("%s\n", v.c_str());
	printf("%s\n", typeid(std::string).name());
	printf("%zx\n", typeid(std::string).hash_code());
}

void test4()
{
	SerializedObject obj1 = SerializedObject();
	std::vector<SerializedData*> list = obj1.getVariables();
	printf("%llu\n", list.size());
	
	for(int i=0; i<list.size(); i++)
	{
		printf("%p\n", list[i]->getData());
	}
}

void test5()
{
	Vec3f v;
	v.x = 1;
	v.y = 0.2;
	v.z = 0.75;

	v.serialize("test1.xml");

}

void test6()
{
	Vec3f v;
	v.deserialize("test1.xml");
	
	

	printf("\n");
	printf("Actual Version:\n");
	printf("\tdouble x = %f\n", v.x);
	printf("\tdouble y = %f\n", v.y);
	printf("\tdouble z = %f\n", v.z);
}

void test7()
{
	SpecialString v = SpecialString("Data1", "Data2");
	SERIALIZE_NOCLASS(v);
	
	v.serialize("test2.xml");
}

void test8()
{
	SerializedObject::init();
	AllDataType d = AllDataType();
	SERIALIZE_NOCLASS(d);

	d.serialize("test3.xml");
	
}

void test9()
{
	SerializedObject::init();
	AllDataType d = AllDataType();
	SERIALIZE_NOCLASS(d);

	d.deserialize("test3.xml");
}

int main()
{
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	// test6();
	// test7();
	// test8();
	test9();
	return 0;
}