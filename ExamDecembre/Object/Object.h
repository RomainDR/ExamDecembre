#pragma once
#include <string>
class Object
{
#pragma region constructor
public:
	Object() = default;
	~Object() = default;
#pragma endregion constructor

#pragma region methods
public:
	virtual std::string ToString();
#pragma endregion methods
};

