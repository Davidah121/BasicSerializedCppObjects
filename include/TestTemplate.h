#pragma once

template<typename T>
class TestTemplate
{
public:
	TestTemplate(T d)
	{
		data = d;
	}
	~TestTemplate()
	{

	}
	T data;
private:
};