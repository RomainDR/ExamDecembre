#pragma once
#include "../Object/Object.h"

class DateTime : public Object
{
#pragma region f/p
private:
	unsigned int day = 0;
	unsigned int month = 0;
	unsigned int year = 0;
#pragma endregion f/p

#pragma region constructor
public:
	DateTime() = default;
	/// <summary>
	/// Constructor to initialize the dateTime class
	/// </summary>
	/// <param name="_day">int</param>
	/// <param name="_month">int</param>
	/// <param name="_year">int</param>
	DateTime(const unsigned int& _day, const unsigned int& _month, const unsigned int& _year);

	/// <summary>
	/// Constructor copy
	/// </summary>
	/// <param name="_copy">DateTime</param>
	DateTime(const DateTime& _copy);
#pragma endregion constructor

#pragma region methods
public:
	/// <summary>
	/// Show the information of class
	/// </summary>
	/// <returns>std::string</returns>
	std::string ToString() override;
#pragma endregion methods

#pragma region operator
public:
	bool operator>(const DateTime* _dt) const;
	bool operator==(const DateTime* _dt) const;
#pragma endregion operator
};

